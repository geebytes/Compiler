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
/// \brief 初始化数据
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
/// \brief 更新信息
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::update_info() {
    exp_check.reset();
    if (info_type == -1) { //重文件更新
        grammars.clear();
        terminal_symbols.clear();
        ui.output_text->clear();
        QString file_name = cfg->get_grammars_path();
        read_grammars(file_name.toStdString());
        file_name = cfg->get_terminal_path();
        read_terminals(file_name.toStdString());
    }

    exp_check.get_grammar(grammars); //重新配置表达式检查器的参数
    exp_check.get_terminal_symbol(terminal_symbols);
    exp_check.make_priority_table();
    update_input();
    last_first_model->clear();
    proirty_model->clear();
    set_first_last(); //刷新信息表
    set_prority_table();
    show_last_first();
    show_prority_table();
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::connect_signal_slot()
///
/// \brief 连接信号与槽函数
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
/// \brief 添加文法的产生式
///
/// \date 2018/6/5
///
/// \param grammar 产生式
///=================================================================================================

void SyntacticAnalyzer::add_grammar(string grammar) {
    grammars.push_back(grammar);
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::add_terminal_symbols(char terminal)
///
/// \brief 添加终结符.
///
/// \date 2018/6/5
///
/// \param terminal 终结符.
///=================================================================================================

void SyntacticAnalyzer::add_terminal_symbols(char terminal) {
    terminal_symbols.insert(terminal);
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::add_exp(string exp)
///
/// \brief 添加表达式
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
/// \brief 读取配置信息
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
/// \brief 从文件导入表达式
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::open_expression() {
    QFileDialog *file_dialog = new QFileDialog(this); //定义文 件对话框类
    file_dialog->setWindowTitle(QString::fromLocal8Bit("打开文件"));     //定义文件对话框标题
    file_dialog->setDirectory("."); //设置默认文件路径
    file_dialog->setNameFilter(tr("file(*.txt)")); //设置文件过滤器
    file_dialog->setFileMode(QFileDialog::ExistingFile); //单个文件
    file_dialog->setViewMode(QFileDialog::Detail); //设置视图模式
    QString file_path;
    if (file_dialog->exec()) {
        QByteArray file_name_btye = file_dialog->selectedFiles()[0].toLocal8Bit(); //每次读取一个文件
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
/// \brief 打开配置窗口
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::open_setting() {
    cfg->show();
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::check_btn()
///
/// \brief 检查表达式
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::check_btn() {
    if (info_type != -1) //判断是否需要更新数据
        update_info();
    ui.output_text->clear(); //清空上一次的输出信息
    vector<string>::iterator it = expressions.begin();
    vector<string>::iterator end = expressions.end();
    step_record.clear(); //清空上一次的分析记录
    int count = 0; //表达式索引
    for (it; it != end; it++) { //遍历表达式，逐条分析

        check_expression(*it, count);
        step_record[count] = exp_check.get_setp();
        count++;
        exp_check.reset();
    }
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::rev_terminal_path(QString path)
///
/// \brief 从配置窗口接收终结符文件路径
///
/// \date 2018/6/5
///
/// \param path 终结符文件的路径.
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
/// \brief 关闭配置窗口
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
/// \brief 待接收的信息的类型
/// 	   0：文法
/// 	   1：表达式
/// 	   2：终结符
///
/// \date 2018/6/5
///
/// \param input_type 类型
///=================================================================================================

void SyntacticAnalyzer::input_info(int input_type) {
    info_type = input_type;
    input->show();
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::input_finish()
///
/// \brief 输入窗口输入完成响应
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::input_finish() {
    vector<string> info_vec = input->get_info();
    input->close();
    if (info_type != -1) {
        if (info_type == 0) { //文法
            grammars.clear();
            grammars = info_vec;
        } else if (info_type == 1) { //表达式
            expressions.clear();
            expressions = info_vec;
        } else { //终结符
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
    update_info(); //更新信息
    info_type = -1;
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::input_grammars()
///
/// \brief 输入文法按钮响应函数
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::input_grammars() {
    emit send_input_type(0);
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::input_exp()
///
/// \brief 输入表达式响应函数
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::input_exp() {
    emit send_input_type(1);
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::input_terminals()
///
/// \brief Input 输入终结符响应函数
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::input_terminals() {
    emit send_input_type(2);
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::update_input()
///
/// \brief 更新输入项信息
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::update_input() {
    ui.input_text->clear(); //清空上一次的信息
    set<char>::iterator it = terminal_symbols.begin();
    set<char>::iterator end = terminal_symbols.end();
    vector<std::string>::iterator gra_it = grammars.begin();
    vector<std::string>::iterator gra_end = grammars.end();
    vector<std::string>::iterator exp_it = expressions.begin();
    vector<std::string>::iterator exp_end = expressions.end();
    ui.input_text->append(QString::fromLocal8Bit("终结符集:"));
    QString terminals = "";
    for (it; it != end; it++) {
        terminals.append(*it).append(" ");
    }
    ui.input_text->append(terminals);
    ui.input_text->append("\n");
    ui.input_text->append(QString::fromLocal8Bit("文法:"));
    for (gra_it; gra_it != gra_end; gra_it++) {
        ui.input_text->append(QString::fromStdString(*gra_it));
    }
    ui.input_text->append("\n");
    ui.input_text->append(QString::fromLocal8Bit("表达式:"));
    for (exp_it; exp_it != exp_end; exp_it++) {
        ui.input_text->append(QString::fromStdString(*exp_it));
    }
    //update_info();
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::show_step(const QUrl &link)
///
/// \brief 显示分析步骤
///
/// \date 2018/6/5
///
/// \param link 输出项中的超链接
///=================================================================================================

void SyntacticAnalyzer::show_step(const QUrl &link) {
    QUrlQuery query(link);
    QString record = query.queryItemValue("record_index"); //获取链接中记录索引参数的值
    qDebug() << "Record index:" << record;
    analysis_setp->clear_table();
    analysis_setp->add_step(step_record[record.toInt()]);
    analysis_setp->show();

}

///=================================================================================================
/// \fn void SyntacticAnalyzer::set_first_last()
///
/// \brief 设置FIRST/LAST集表格的样式
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
/// \brief 设置优先关系表的样式
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
/// \brief 显示FIRST/LAST集
///
/// \date 2018/6/5
///=================================================================================================

void SyntacticAnalyzer::show_last_first() {
    map<char, set<char>> first = exp_check.get_first(); //FIRST集
    map<char, set<char>> last = exp_check.get_last();
    map<char, set<char>>::iterator first_it = first.begin();
    map<char, set<char>>::iterator first_end = first.end();
    map<char, set<char>>::iterator last_it = last.begin(); //LAST集
    map<char, set<char>>::iterator last_end = last.end();
    set<char>::iterator it;
    set<char>::iterator end;
    int size = first.size();
    last_first_model->setRowCount(size);
    int row = 0;
    int col = 0;
    for (first_it; first_it != first_end; first_it++) { //显示FIRST集
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
    for (last_it; last_it != last_end; last_it++) { //显示LAST集
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
/// \brief 显示优先关系表
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
/// \brief 检测表达式
/// 	   并为每一条表达式或错误信息生成一条超链接，
/// 	   链接包含该表达式在分析步骤记录器中的索引。
///
/// \date 2018/6/5
///
/// \param exp		    表达式.
/// \param record_index 表达式的索引
///=================================================================================================

void SyntacticAnalyzer::check_expression(string exp, int record_index) {

    exp_check.check_expression(exp);

    map<int, string> error = exp_check.get_error();
    map<int, string>::iterator it = error.begin();
    map<int, string>::iterator end = error.end();
    QString error_info = "";
    if (error.empty()) //表达式生成超链接
        ui.output_text->append(QString("<html><p><a href=\"goto://setp?record_index=%1\">%2</a></p></html>").arg(record_index).arg(QString::fromStdString(exp)));
    else
        ui.output_text->append(QString::fromStdString(exp));
    qDebug() << QString::fromStdString(exp);
    for (it; it != end; it++) { //高亮错误

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
        //去掉空格
        cursor.setPosition(postion - 1, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::NoMove, QTextCursor::MoveAnchor, 0);
        cursor.deleteChar();
        cursor.setPosition(postion, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::NoMove, QTextCursor::MoveAnchor, 0);
        cursor.deleteChar();
    }
    for (it = error.begin(); it != end; it++) { //错误记录生成超链接

        ui.output_text->append(QString("<html><p><a href=\"goto://setp?record_index=%1\">%2:%3</a></p></html>").arg(record_index).arg(it->first).arg(QString::fromLocal8Bit(it->second.data())));
    }
}

///=================================================================================================
/// \fn void SyntacticAnalyzer::read_grammars(string file_name)
///
/// \brief 从文件中读取文法
///
/// \date 2018/6/5
///
/// \param file_name 文件路径
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
/// \brief 从文件中读取终结符集
///
/// \date 2018/6/5
///
/// \param file_name 文件路径
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
/// \brief 从文件中读取表达式
///
/// \date 2018/6/5
///
/// \param file_name 文件路径
///=================================================================================================

void SyntacticAnalyzer::read_exp(string file_name) {
    ifstream fin(file_name);
    string line;
    while (getline(fin, line)) {
        add_exp(line);
    }
    fin.close();
}
