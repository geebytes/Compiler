#include "Config.h"
#include <QDebug>
Config::Config(QWidget *parent)
    : QWidget(parent) {
    ui.setupUi(this);
    connect(ui.open_terminals, SIGNAL(clicked()), this, SLOT(open_terminal()));
    connect(ui.open_garmms, SIGNAL(clicked()), this, SLOT(open_grammars()));
    connect(ui.ok, SIGNAL(clicked()), this, SLOT(ok_btn()));
    connect(this, SIGNAL(file_type_send(int)), this, SLOT(open_file(int)));
    read_setting();
}


void Config::connect_signal_slot() {
    connect(ui.open_terminals, SIGNAL(clicked()), this, SLOT(open_terminal()));
    connect(ui.open_garmms, SIGNAL(clicked()), this, SLOT(open_grammars()));
    connect(ui.ok, SIGNAL(clicked()), this, SLOT(ok_btn()));
    connect(this, SIGNAL(file_type_send(int)), this, SLOT(open_file(int)));
}

QString Config::get_grammars_path() {
    return ui.garmmars_path->text();
}

QString Config::get_terminal_path() {
    return ui.terminals_path->text();
}

Config::~Config() {
}

void Config::open_file(int file_type) {
    qDebug() << "open";
    QFileDialog *file_dialog = new QFileDialog(this); //定义文 件对话框类
    file_dialog->setWindowTitle(QString::fromLocal8Bit("打开文件"));     //定义文件对话框标题
    file_dialog->setDirectory("."); //设置默认文件路径
    file_dialog->setNameFilter(tr("file(*.txt)")); //设置文件过滤器
    file_dialog->setFileMode(QFileDialog::ExistingFile); //单个文件
    file_dialog->setViewMode(QFileDialog::Detail); //设置视图模式
    QString file_path;
    if (file_dialog->exec()) {
        QByteArray file_name_btye = file_dialog->selectedFiles()[0].toLocal8Bit();
        std::string file_name = file_name_btye.toStdString();
        file_path = QFileInfo(QString::fromStdString(file_name)).absoluteFilePath();
        if (file_type == 0) {
            teminanls_path = file_path;
            ui.terminals_path->setText(file_path);

        } else {
            grammars_path = file_path;
            ui.garmmars_path->setText(file_path);
        }

    }
    delete file_dialog;
}

void Config::read_setting() {
    QSettings *read = new QSettings("config.ini", QSettings::IniFormat);
    QString file_name = QFileInfo(QString::fromLocal8Bit(read->value("/path/terminals").toByteArray())).absoluteFilePath();
    ui.terminals_path->setText(file_name);
    file_name = QFileInfo(QString::fromLocal8Bit(read->value("/path/grammars").toByteArray())).absoluteFilePath();
    ui.garmmars_path->setText(file_name);
    delete read;
}

void Config::wirte_setting() {
    QSettings *write = new QSettings("config.ini", QSettings::IniFormat);
    QString file_name = ui.terminals_path->text();
    write->setValue("/path/terminals", file_name);
    file_name = ui.garmmars_path->text();
    write->setValue("/path/grammars", file_name);
    delete write;
}

void Config::open_terminal() {
    emit file_type_send(0);
}

void Config::open_grammars() {
    emit file_type_send(1);
}

void Config::ok_btn() {
    emit finish();
    emit teminanls_file(ui.terminals_path->text());
    emit grammars_file(ui.garmmars_path->text());
    wirte_setting();

}
