#include "InputInfo.h"
#include<QStringList>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
InputInfo::InputInfo(QWidget *parent)
    : QWidget(parent) {
    ui.setupUi(this);
    connect(ui.input_finish, SIGNAL(clicked()), this, SLOT(input_finish()));
}

std::vector<string> InputInfo::get_info() {
    return info;
}

InputInfo::~InputInfo() {
}

void InputInfo::input_finish() {
    info.clear();
    QStringList list = ui.input_edit->toPlainText().split("\n");
    for (int i = 0; i < list.size(); i++) {
        info.push_back(list[i].toStdString());
    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromLocal8Bit("输入完成"), QString::fromLocal8Bit("是否保存该信息？"),
                                  QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (reply == QMessageBox::Yes) {
        QString file_name = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("保存信息"), "", tr("*.txt"));
        if (!file_name.isNull()) {
            QFile file(file_name);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
                QMessageBox::warning(this, QString::fromLocal8Bit("信息保存"), QString::fromLocal8Bit("无法信息保存!"), QMessageBox::Yes);
            }
            QTextStream in(&file);
            in << ui.input_edit->toPlainText();
            file.close();
        }
    }
    emit finish();
}
