#pragma once

#include <QStandardItemModel>
#include <QWidget>
#include <QObject>
class TableModel : public QStandardItemModel {
    Q_OBJECT

  public:
    TableModel(QObject *parent = Q_NULLPTR): QStandardItemModel() {}
    ~TableModel();
    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
};
