#ifndef ARX_DIALOG_H
#define ARX_DIALOG_H

#include <QDialog>

namespace Ui {
class arx_dialog;
}

class arx_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit arx_dialog(QWidget *parent = nullptr);
    ~arx_dialog();

private:
    Ui::arx_dialog *ui;
};

#endif // ARX_DIALOG_H
