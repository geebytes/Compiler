#include "tablemodel.h"


TableModel::~TableModel() {


}

QVariant TableModel::data(const QModelIndex &idx, int role /*= Qt::DisplayRole*/) const {
    QVariant value = QStandardItemModel::data(idx, role);
    if (Qt::TextAlignmentRole == role) {
        value = int(Qt::AlignCenter | Qt::AlignHCenter);
        return value;
    }
    return value;
}
