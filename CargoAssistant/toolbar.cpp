#include "toolbar.h"
#include "panel.h"

#include <QToolBar>
#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QToolButton>
#include <QTranslator>

ToolBar::ToolBar(QWidget *parent, QString picsPath): QToolBar(parent)
{
    m_panel = new QWidget();
    m_table = new QTableWidget();

    setIconSize(QSize(40, 40));
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    setPicsPath(picsPath);
    addQuitButton(parent);
    addDrawAreaButton(parent);
    addLoadDataButton(parent, m_table);
   // addLanguageButton(parent);

}


void ToolBar::setPicsPath(QString path)
{
    this->imageFolderPath = path;
}

void ToolBar::setGridObj(QTableWidget *table)
{
    m_table = table;
}

void ToolBar::setPlaneName(QString name)
{
    m_planeName = name;
    emit planeChanged();
}

QString ToolBar::planeName()
{
    return m_planeName;
}



void ToolBar::setPresetWidget(QWidget *panel)
{
    m_panel = panel;
}


void ToolBar::addQuitButton(QWidget *Window)
{
    QPixmap pix(":/icons/quit");
    QAction *acQuit = new QAction(QIcon(pix),"&Quit", Window);
    connect(acQuit, &QAction::triggered, qApp, QApplication::quit);

    this->addAction(acQuit);
    this->addSeparator();
}

void ToolBar::addLoadDataButton(QWidget *Window, QTableWidget *t)
{
    QPixmap pix(":/icons/loadData");
    QAction *acLoadData = new QAction(QIcon(pix),"&Load Data", Window);
    connect(acLoadData, &QAction::triggered, [this](){
        QStringList slData = {};
        QString fileName = QFileDialog::getOpenFileName(this, tr("Cargo A.."), QApplication::applicationDirPath(), tr("Comma-separated values (*.csv)"));
        if (fileName.isEmpty()){
                QMessageBox::warning(this, "Cargo. Ass.", "No file selected!");
                return ;
        }
        QFile csv(fileName);
        if (csv.open(QIODevice::ReadOnly | QIODevice::Text)){
            while (!csv.atEnd()) {
                slData.append(csv.readLine());
            }
        }
        csv.close();
        this->drawGrid(slData);
        this->drawTree(slData);
        this->addSeparator();
    });
    this->addAction(acLoadData);
}

void ToolBar::addDrawAreaButton(QWidget *Window)
{
    QPixmap pix(":/icons/cargoPlane");
    QAction *acDrawArea = new QAction(QIcon(pix),"&Draw Plane", Window);
    connect(acDrawArea, &QAction::triggered, [Window](){ });
}

void ToolBar::addLanguageButton(QWidget *Window)
{
    QPixmap pix(":/new/prefix1/Tongue");
    QToolButton *tongueBtn = new QToolButton(Window);
    tongueBtn->setIcon(pix);
    tongueBtn->setText("Lang&uage");
    tongueBtn->setPopupMode(QToolButton::InstantPopup);
    this->addWidget(tongueBtn);
}

void ToolBar::createLanguageMenu()
{



}

void ToolBar::drawGrid(QStringList sl)
{
    m_table->clear();
    QString h = sl.at(0).trimmed();
    QStringList slHeader = h.split(';');
    sl.removeAt(0);
    m_table->setRowCount(sl.count());
    m_table->setColumnCount(slHeader.count());
    m_table->setHorizontalHeaderLabels(slHeader);
    m_table->setStyleSheet("QHeaderView::section {background-color:#f0f0f0;border-style: outset;}"
                           "QTableCornerButton::section {background: #f0f0f0;border-style: outset;}");
    for (int r= 0; r<sl.count(); r++){
        QStringList slRow = sl.at(r).split(';');
        for (int c = 0; c < slRow.count(); c++)
        {
            QTableWidgetItem *item =  new QTableWidgetItem(slRow.at(c).trimmed());
            m_table->setItem(r, c, item);
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        }
        slRow.clear();
    }
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->resizeRowsToContents();
    m_table->resizeColumnsToContents();
}

void ToolBar::drawTree(QStringList sl)
{

}
