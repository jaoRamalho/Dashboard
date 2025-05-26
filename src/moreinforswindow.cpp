#include "include/moreinforswindow.h"

moreinforswindow::moreinforswindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::moreinforswindow)
{
    ui->setupUi(this);
}

moreinforswindow::~moreinforswindow()
{
    delete ui;
}
// INDICACAO DE COMO CHAMAR A FUNCAO
// connect(ui->tableWidget, &QTableWidget::cellClicked,
//             this, &MainWindow::on_tableWidget_cellClicked);
// FUNCAO CHAMADA AO QUERER MOSTRAR A NOVA JANELA
// DEVE ESTAR DENTRO DA WINDOW ORIGINAL
//--->>
// void MainWindow::on_tableWidget_cellClicked(int row, int column)
// {
//     Q_UNUSED(row);
//     Q_UNUSED(column);

//     // Abrir nova janela
//     NovaJanela *janela = new NovaJanela(this);
//     janela->setModal(true);  // opcional: bloqueia a janela principal
//     janela->exec();          // mostra a janela como diálogo modal
// }

