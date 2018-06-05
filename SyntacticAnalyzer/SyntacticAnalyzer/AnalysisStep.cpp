#include "AnalysisStep.h"

AnalysisStep::AnalysisStep(QWidget *parent)
    : QWidget(parent) {
    ui.setupUi(this);
    setp_model = new TableModel;
    ui.setp_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    init_table();

}

void AnalysisStep::add_step(map<int, vector<string>> setp) {
    map<int, vector<string>>:: iterator it  = setp.begin();
    map<int, vector<string>>::iterator end = setp.end();
    vector<string>::iterator str_it;
    vector<string>::iterator str_end;
    int row = 0;
    int col = 0;
    for (it; it != end; it++) {
        int size = it->second.size();
        //qDebug() << "size=" << QString("%1").arg(size);
        //setp_model->setHeaderData(row, Qt::Vertical, QString("%1").arg(it->first));
        col = 0;
        setp_model->setItem(row, col, new QStandardItem(QString("%1").arg(it->first)));
        str_it = it->second.begin();
        str_end = it->second.end();
        for (str_it; str_it != str_end; str_it++) {
            setp_model->setItem(row, col, new QStandardItem(QString::fromLocal8Bit(str_it->data())));
            col++;
        }
        row++;
    }
}

void AnalysisStep::clear_table() {
    setp_model->clear();
    init_table();
}

AnalysisStep::~AnalysisStep() {
    delete setp_model;
}

void AnalysisStep::init_table() {
    setp_model->setColumnCount(5);
    //setp_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("²½Öè"));
    setp_model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("·ûºÅÕ»×´Ì¬"));
    setp_model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("¹ØÏµ"));
    setp_model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("ÊäÈë´®×´Ì¬"));
    setp_model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("×î¶ÌËØ¶ÌÓï"));
    setp_model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("¶¯×÷"));
    ui.setp_table->setModel(setp_model);
    ui.setp_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui.setp_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
