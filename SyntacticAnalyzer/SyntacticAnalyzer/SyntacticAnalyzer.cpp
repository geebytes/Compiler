#include "SyntacticAnalyzer.h"

SyntacticAnalyzer::SyntacticAnalyzer(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    ui.output_text->setOpenExternalLinks(false);
    ui.output_text->setOpenLinks(false);
    init();
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::init()
///
/// \brief ��ʼ������
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::init() {
    settings = new QSettings("config.ini", QSettings::IniFormat);
    get_settings();
    cfg = new Config();
    input = new InputInfo();
    last_first_model = new TableModel;
    proirty_model = new TableModel;
    analysis_setp = new AnalysisStep;
    info_type = -1;
    ui.lastView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    update_input();
    exp_check.get_grammar(grammars);
    exp_check.get_terminal_symbol(terminal_symbols);
    exp_check.make_priority_table();
    connect_signal_slot();
    set_first_last();
    set_prority_table();
    show_last_first();
    show_prority_table();
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::update_info()
///
/// \brief ������Ϣ
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::update_info() {
    exp_check.reset();
    if (info_type == -1) { //���ļ�����
        grammars.clear();
        terminal_symbols.clear();
        ui.output_text->clear();
        QString file_name = cfg->get_grammars_path();
        read_grammars(file_name.toStdString());
        file_name = cfg->get_terminal_path();
        read_terminals(file_name.toStdString());
    }

    exp_check.get_grammar(grammars); //�������ñ��ʽ������Ĳ���
    exp_check.get_terminal_symbol(terminal_symbols);
    exp_check.make_priority_table();
    update_input();
    last_first_model->clear();
    proirty_model->clear();
    set_first_last(); //ˢ����Ϣ��
    set_prority_table();
    show_last_first();
    show_prority_table();
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::connect_signal_slot()
///
/// \brief �����ź���ۺ���
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::connect_signal_slot() {
    connect(ui.check, SIGNAL(triggered()), this, SLOT(check_btn()));
    connect(ui.open_exp, SIGNAL(triggered()), this, SLOT(open_expression()));
    connect(ui.read_settings, SIGNAL(triggered()), this, SLOT(open_setting()));
    connect(cfg, SIGNAL(teminanls_file(QString)), this, SLOT(rev_terminal_path(QString)));
    connect(cfg, SIGNAL(grammars_file(QString)), this, SLOT(rev_grammars_path(QString)));
    connect(cfg, SIGNAL(finish()), this, SLOT(close_cfg()));
    connect(cfg, SIGNAL(finish()), this, SLOT(update_info()));
    connect(this, SIGNAL(send_input_type(int)), this, SLOT(input_info(int)));
    connect(ui.input_grammars, SIGNAL(triggered()), this, SLOT(input_grammars()));
    connect(ui.input_treminal, SIGNAL(triggered()), this, SLOT(input_terminals()));
    connect(ui.input_exp, SIGNAL(triggered()), this, SLOT(input_exp()));
    connect(input, SIGNAL(finish()), this, SLOT(input_finish()));
    connect(ui.output_text, SIGNAL(anchorClicked(const QUrl&)), this, SLOT(show_step(const QUrl&)));
}
SyntacticAnalyzer::~SyntacticAnalyzer() {
    delete settings;
    delete cfg;
    delete last_first_model;
    delete proirty_model;
    delete input;
    delete analysis_setp;

}

///=================================================================================================
/// \fn void SyntacticAnalyzer::add_grammar(string grammar)
///
/// \brief ����ķ��Ĳ���ʽ
///
/// \date 2018/6/5
///
/// \param grammar ����ʽ
///=================================================================================================

void SyntacticAnalyzer::add_grammar(string grammar) {
    grammars.push_back(grammar);
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::add_terminal_symbols(char terminal)
///
/// \brief ����ս��.
///
/// \date 2018/6/5
///
/// \param terminal �ս��.
///=================================================================================================

void SyntacticAnalyzer::add_terminal_symbols(char terminal) {
    terminal_symbols.insert(terminal);
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::add_exp(string exp)
///
/// \brief ��ӱ��ʽ
///
/// \date 2018/6/5
///
/// \param exp The exponent.
///=================================================================================================

void SyntacticAnalyzer::add_exp(string exp) {
    expressions.push_back(exp);
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::get_settings()
///
/// \brief ��ȡ������Ϣ
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::get_settings() {
    QString file_name = QFileInfo(QString::fromLocal8Bit(settings->value("/path/terminals").toByteArray())).absoluteFilePath();
    read_terminals(file_name.toStdString());
    file_name = QFileInfo(QString::fromLocal8Bit(settings->value("/path/grammars").toByteArray())).absoluteFilePath();
    read_grammars(file_name.toStdString());
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::open_expression()
///
/// \brief ���ļ�������ʽ
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::open_expression() {
    QFileDialog *file_dialog = new QFileDialog(this); //������ ���Ի�����
    file_dialog->setWindowTitle(QString::fromLocal8Bit("���ļ�"));     //�����ļ��Ի������
    file_dialog->setDirectory("."); //����Ĭ���ļ�·��
    file_dialog->setNameFilter(tr("file(*.txt)")); //�����ļ�������
    file_dialog->setFileMode(QFileDialog::ExistingFile); //�����ļ�
    file_dialog->setViewMode(QFileDialog::Detail); //������ͼģʽ
    QString file_path;
    if (file_dialog->exec()) {
        QByteArray file_name_btye = file_dialog->selectedFiles()[0].toLocal8Bit(); //ÿ�ζ�ȡһ���ļ�
        std::string file_name = file_name_btye.toStdString();
        file_path = QFileInfo(QString::fromStdString(file_name)).absoluteFilePath();
        expressions.clear();
        read_exp(file_path.toStdString());
        update_input();
    }
    delete file_dialog;
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::open_setting()
///
/// \brief �����ô���
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::open_setting() {
    cfg->show();
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::check_btn()
///
/// \brief �����ʽ
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::check_btn() {
    if (info_type != -1) //�ж��Ƿ���Ҫ��������
        update_info();
    ui.output_text->clear(); //�����һ�ε������Ϣ
    vector<string>::iterator it = expressions.begin();
    vector<string>::iterator end = expressions.end();
    step_record.clear(); //�����һ�εķ�����¼
    int count = 0; //���ʽ����
    for (it; it != end; it++) { //�������ʽ����������

        check_expression(*it, count);
        step_record[count] = exp_check.get_setp();
        count++;
        exp_check.reset();
    }
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::rev_terminal_path(QString path)
///
/// \brief �����ô��ڽ����ս���ļ�·��
///
/// \date 2018/6/5
///
/// \param path �ս���ļ���·��.
///=================================================================================================

void SyntacticAnalyzer::rev_terminal_path(QString path) {
    terminal_symbols.clear();
    read_terminals(path.toStdString());
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::rev_grammars_path(QString path)
///
/// \brief Reverse grammars path.
///
/// \date 2018/6/5
///
/// \param path Full pathname of the file.
///=================================================================================================

void SyntacticAnalyzer::rev_grammars_path(QString path) {
    grammars.clear();
    read_grammars(path.toStdString());
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::close_cfg()
///
/// \brief �ر����ô���
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::close_cfg() {
    if (cfg->isVisible())
        cfg->close();
    ui.input_text->clear();
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::input_info(int input_type)
///
/// \brief �����յ���Ϣ������
/// 	   0���ķ�
/// 	   1�����ʽ
/// 	   2���ս��
///
/// \date 2018/6/5
///
/// \param input_type ����
///=================================================================================================

void SyntacticAnalyzer::input_info(int input_type) {
    info_type = input_type;
    input->show();
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::input_finish()
///
/// \brief ���봰�����������Ӧ
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::input_finish() {
    vector<string> info_vec = input->get_info();
    input->close();
    if (info_type != -1) {
        if (info_type == 0) { //�ķ�
            grammars.clear();
            grammars = info_vec;
        } else if (info_type == 1) { //���ʽ
            expressions.clear();
            expressions = info_vec;
        } else { //�ս��
            terminal_symbols.clear();
            vector<string>::iterator it = info_vec.begin();
            vector<string>::iterator end = info_vec.end();
            for (it; it != end; it++) {

                for (int i = 0; i < it->length(); i++) {
                    if(it->at(i) != ' ' || it->at(i) != '\n' || it->at(i) != '\t')
                        terminal_symbols.insert(it->at(i));
                }
            }
        }
    }
    update_info(); //������Ϣ
    info_type = -1;
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::input_grammars()
///
/// \brief �����ķ���ť��Ӧ����
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::input_grammars() {
    emit send_input_type(0);
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::input_exp()
///
/// \brief ������ʽ��Ӧ����
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::input_exp() {
    emit send_input_type(1);
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::input_terminals()
///
/// \brief Input �����ս����Ӧ����
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::input_terminals() {
    emit send_input_type(2);
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::update_input()
///
/// \brief ������������Ϣ
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::update_input() {
    ui.input_text->clear(); //�����һ�ε���Ϣ
    set<char>::iterator it = terminal_symbols.begin();
    set<char>::iterator end = terminal_symbols.end();
    vector<std::string>::iterator gra_it = grammars.begin();
    vector<std::string>::iterator gra_end = grammars.end();
    vector<std::string>::iterator exp_it = expressions.begin();
    vector<std::string>::iterator exp_end = expressions.end();
    ui.input_text->append(QString::fromLocal8Bit("�ս����:"));
    QString terminals = "";
    for (it; it != end; it++) {
        terminals.append(*it).append(" ");
    }
    ui.input_text->append(terminals);
    ui.input_text->append("\n");
    ui.input_text->append(QString::fromLocal8Bit("�ķ�:"));
    for (gra_it; gra_it != gra_end; gra_it++) {
        ui.input_text->append(QString::fromStdString(*gra_it));
    }
    ui.input_text->append("\n");
    ui.input_text->append(QString::fromLocal8Bit("���ʽ:"));
    for (exp_it; exp_it != exp_end; exp_it++) {
        ui.input_text->append(QString::fromStdString(*exp_it));
    }
    //update_info();
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::show_step(const QUrl &link)
///
/// \brief ��ʾ��������
///
/// \date 2018/6/5
///
/// \param link ������еĳ�����
///=================================================================================================

void SyntacticAnalyzer::show_step(const QUrl &link) {
    QUrlQuery query(link);
    QString record = query.queryItemValue("record_index"); //��ȡ�����м�¼����������ֵ
    qDebug() << "Record index:" << record;
    analysis_setp->clear_table();
    analysis_setp->add_step(step_record[record.toInt()]);
    analysis_setp->show();

}

///=================================================================================================
/// \fn void SyntacticAnalyzer::set_first_last()
///
/// \brief ����FIRST/LAST��������ʽ
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::set_first_last() {

    last_first_model->setColumnCount(2);
    last_first_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("FIRST"));
    last_first_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("LAST"));
    ui.lastView->setModel(last_first_model);
    ui.lastView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui.lastView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::set_prority_table()
///
/// \brief �������ȹ�ϵ�����ʽ
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::set_prority_table() {
    set<char>::iterator it = terminal_symbols.begin();
    set<char>::iterator end = terminal_symbols.end();
    int size = terminal_symbols.size();
    proirty_model->setColumnCount(size);
    proirty_model->setRowCount(size);
    int index = 0;
    for (it; it != end; it++) {
        proirty_model->setHeaderData(index, Qt::Horizontal, QString("").append(*it));
        proirty_model->setHeaderData(index, Qt::Vertical, QString("").append(*it));
        index++;
    }
    ui.tableView->setModel(proirty_model);
    ui.lastView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui.lastView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::show_last_first()
///
/// \brief ��ʾFIRST/LAST��
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::show_last_first() {
    map<char, set<char>> first = exp_check.get_first(); //FIRST��
    map<char, set<char>> last = exp_check.get_last();
    map<char, set<char>>::iterator first_it = first.begin();
    map<char, set<char>>::iterator first_end = first.end();
    map<char, set<char>>::iterator last_it = last.begin(); //LAST��
    map<char, set<char>>::iterator last_end = last.end();
    set<char>::iterator it;
    set<char>::iterator end;
    int size = first.size();
    last_first_model->setRowCount(size);
    int row = 0;
    int col = 0;
    for (first_it; first_it != first_end; first_it++) { //��ʾFIRST��
        QString terminals = "";
        last_first_model->setHeaderData(row, Qt::Vertical, QString("").append(first_it->first));
        it = first_it->second.begin();
        end = first_it->second.end();
        for (it; it != end; it++) {
            terminals.append(*it).append("  ");
        }
        last_first_model->setItem(row, col, new QStandardItem(terminals));
        row++;
    }
    row = 0;
    col++;
    for (last_it; last_it != last_end; last_it++) { //��ʾLAST��
        QString terminals = "";
        it = last_it->second.begin();
        end = last_it->second.end();
        for (it; it != end; it++) {
            terminals.append(*it).append("  ");
        }

        last_first_model->setItem(row, col, new QStandardItem(terminals));
        row++;
    }

}

///=================================================================================================
/// \fn void SyntacticAnalyzer::show_prority_table()
///
/// \brief ��ʾ���ȹ�ϵ��
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::show_prority_table() {
    map<pair<char, char>, char> prority_table = exp_check.get_priority_table();
    set<char>::iterator row_it = terminal_symbols.begin();
    set<char>::iterator row_end = terminal_symbols.end();
    set<char>::iterator col_it = terminal_symbols.begin();
    set<char>::iterator col_end = terminal_symbols.end();
    int row = 0;
    int col = 0;
    for (row_it; row_it != row_end; row_it++) {
        col_it = terminal_symbols.begin();
        col_end = terminal_symbols.end();
        col = 0;
        for (col_it; col_it != col_end; col_it++) {
            QString prority = QString("").append(prority_table[make_pair(*row_it, *col_it)]);
            proirty_model->setItem(row, col, new QStandardItem(prority));
            col++;
        }
        row++;
    }
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::check_expression(string exp, int record_index)
///
/// \brief �����ʽ
/// 	   ��Ϊÿһ�����ʽ�������Ϣ����һ�������ӣ�
/// 	   ���Ӱ����ñ��ʽ�ڷ��������¼���е�������
///
/// \date 2018/6/5
///
/// \param exp		    ���ʽ.
/// \param record_index ���ʽ������
///=================================================================================================

void SyntacticAnalyzer::check_expression(string exp, int record_index) {

    exp_check.check_expression(exp);

    map<int, string> error = exp_check.get_error();
    map<int, string>::iterator it = error.begin();
    map<int, string>::iterator end = error.end();
    QString error_info = "";
    if (error.empty()) //���ʽ���ɳ�����
        ui.output_text->append(QString("<html><p><a href=\"goto://setp?record_index=%1\">%2</a></p></html>").arg(record_index).arg(QString::fromStdString(exp)));
    else
        ui.output_text->append(QString::fromStdString(exp));
    qDebug() << QString::fromStdString(exp);
    for (it; it != end; it++) { //��������

        QTextCursor cursor(ui.output_text->document());
        QTextCursor cursor_postion(ui.output_text->textCursor());
        QTextCharFormat color_format;
        color_format.setForeground(Qt::red);
        int postion = cursor_postion.position() - (exp.length() - it->first);
        cursor.setPosition(postion - 1, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::NoMove, QTextCursor::MoveAnchor, 0);
        cursor.insertText(" ");
        cursor.setPosition(postion + 1, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::NoMove, QTextCursor::MoveAnchor, 0);
        cursor.insertText(" ");
        postion = cursor_postion.position() - (exp.length() + 2 - it->first);
        cursor.setPosition(postion, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::NoMove, QTextCursor::MoveAnchor, 1);
        cursor.select(QTextCursor::WordUnderCursor);
        cursor.mergeCharFormat(color_format);
        //ȥ���ո�
        cursor.setPosition(postion - 1, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::NoMove, QTextCursor::MoveAnchor, 0);
        cursor.deleteChar();
        cursor.setPosition(postion, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::NoMove, QTextCursor::MoveAnchor, 0);
        cursor.deleteChar();
    }
    for (it = error.begin(); it != end; it++) { //�����¼���ɳ�����

        ui.output_text->append(QString("<html><p><a href=\"goto://setp?record_index=%1\">%2:%3</a></p></html>").arg(record_index).arg(it->first).arg(QString::fromLocal8Bit(it->second.data())));
    }
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::read_grammars(string file_name)
///
/// \brief ���ļ��ж�ȡ�ķ�
///
/// \date 2018/6/5
///
/// \param file_name �ļ�·��
///=================================================================================================

void SyntacticAnalyzer::read_grammars(string file_name) {
    ifstream fin(file_name);
    string line;
    while (getline(fin, line)) {
        add_grammar(line);
    }
    fin.close();
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::read_terminals(string file_name)
///
/// \brief ���ļ��ж�ȡ�ս����
///
/// \date 2018/6/5
///
/// \param file_name �ļ�·��
///=================================================================================================

void SyntacticAnalyzer::read_terminals(string file_name) {
    ifstream fin(file_name);
    char terminal;
    while (fin >> terminal) {
        add_terminal_symbols(terminal);
    }
    fin.close();
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::read_exp(string file_name)
///
/// \brief ���ļ��ж�ȡ���ʽ
///
/// \date 2018/6/5
///
/// \param file_name �ļ�·��
///=================================================================================================

void SyntacticAnalyzer::read_exp(string file_name) {
    ifstream fin(file_name);
    string line;
    while (getline(fin, line)) {
        add_exp(line);
    }
    fin.close();
}
