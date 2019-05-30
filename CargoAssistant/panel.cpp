#include "panel.h"
#include "toolbar.h"


#include <QWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QFile>
#include <QFileInfo>
#include <QApplication>
#include <QTextStream>
#include <QMessageBox>
#include <QRadioButton>
#include <QFormLayout>

int undoMsg(QLabel *lb){
    QString value = lb->text().trimmed();
    if (value.indexOf('(') > 0){
        value.truncate(value.indexOf('('));
    }
    return QMessageBox::warning(nullptr, "Cargo Ass.", QString("Parameter ''%1'' not valid!").arg(value));
}

bool checkIsValidValue(QWidget *w)
{
    bool result = false;
    if(dynamic_cast<const QLineEdit*>(w) != nullptr){
        if (dynamic_cast<const QLineEdit*>(w)->text().length()>0) {result = true;}
    }
    if(dynamic_cast<const QDoubleSpinBox*>(w) != nullptr){
        if (dynamic_cast<const QDoubleSpinBox*>(w)->value()>0.00) {result = true;}
    }
    if(dynamic_cast<const QSpinBox*>(w) != nullptr){
        if (dynamic_cast<const QSpinBox*>(w)->value()>0) {result = true;}
    }
    return result;
}


Panel::Panel(QWidget *parent)
{

    this->setParent(parent);

    QGroupBox *gbMng = new QGroupBox("Presets");
    QGroupBox *gbSetPresets = new QGroupBox("Details");
    QGroupBox *gbLayers= new QGroupBox("Layers");
    QGroupBox *gbPosDir = new QGroupBox("Position");
    QGroupBox *gbRestDir = new QGroupBox("Rest by");
    QGroupBox *gbVolume = new QGroupBox("Volume");

    QVBoxLayout *vblPanel  = new QVBoxLayout(this);
    QVBoxLayout *vblDefSets = new QVBoxLayout(gbMng);
    QFormLayout *flPreSets = new QFormLayout(gbSetPresets);
    QFormLayout *flLay = new QFormLayout(gbLayers);
    QHBoxLayout *vblPos = new QHBoxLayout(gbPosDir);
    QHBoxLayout *vblRest = new QHBoxLayout(gbRestDir);
    QHBoxLayout *vhlVolume = new QHBoxLayout(gbVolume);

    QLabel *lbSelect = new QLabel("Select preset ");
    QLabel *lbNewPreset = new QLabel("Preset name");
    QLabel *lbLen = new QLabel("Inner Lenght(m)");
    QLabel *lbWid = new QLabel("Inner Width(m)");
    QLabel *lbHei = new QLabel("Inner Height(m)");
    QLabel *lbWei = new QLabel("Max Weight(kg³)");
    QLabel *lbLay = new QLabel("Quantity");
    QLabel *lbPcs = new QLabel("Pieces");


    lbVolumeValue = new QLabel("0.00");
    lbVolumeValue->text().replace(QLatin1Char('.'), QLocale().decimalPoint());
    QLabel *lbVolumeUnit = new QLabel(" m³");


    QFont font("Times",18, QFont::Bold);
    lbVolumeUnit->setFont(font);
    lbVolumeValue->setFont(font);

    sPath = QApplication::applicationDirPath()+tr("debugPresets.csv");
    slPresets = new QStringList(loadPresetList());
    slNames = new QStringList(loadNamesList());

    leName = new QLineEdit("");
    leName->setDisabled(true);
    lbNewPreset->setBuddy(leName);

    pbLoadPreset = new QPushButton("Load &presets");
    pbNewPreset = new QPushButton("&New preset");
    pbDeletePreset = new QPushButton("&Delete preset");


    dsbLen = new QDoubleSpinBox();
    dsbLen->setMaximum(100.00);
    dsbLen->setDisabled(true);
    lbLen->setBuddy(dsbLen);


    dsbWid = new QDoubleSpinBox();
    dsbWid->setMaximum(100.00);
    dsbWid->setDisabled(true);
    lbWid->setBuddy(dsbWid);

    dsbHei = new QDoubleSpinBox();
    dsbHei->setMaximum(100.00);
    dsbHei->setDisabled(true);
    lbHei->setBuddy(dsbHei);

    dsbWei = new QDoubleSpinBox();
    dsbWei->setMaximum(100.00);
    dsbWei->setDisabled(true);
    lbWei->setBuddy(dsbWei);

    cbDefSets = new QComboBox();
    cbDefSets->addItems(loadNamesList());
    cbDefSets->setCurrentIndex(-1);
    lbSelect->setBuddy(cbDefSets);

    pbSavePreset = new QPushButton("&Save preset");
    pbSavePreset->setDisabled(true);

    sbLayersNum= new QSpinBox();
    sbLayersNum->setMaximum(100.00);
    sbLayersNum->setDisabled(true);
    lbLay->setBuddy(sbLayersNum);

    sbPiecesNum= new QSpinBox();
    sbPiecesNum->setMaximum(100.00);
    sbPiecesNum->setDisabled(true);
    lbPcs->setBuddy(sbPiecesNum);


    rbHorPos = new QRadioButton("&Horizontal");
    rbVertPos = new QRadioButton("&Vertical");
    rbSideRest = new QRadioButton("S&ide");
    rbPlaneRest = new QRadioButton("Pl&ane");

    vblPos->addWidget(rbHorPos);
    vblPos->addWidget(rbVertPos);

    vblRest->setSpacing(0);
    vblRest->addWidget(rbSideRest);
    vblRest->addWidget(rbPlaneRest);

    vblDefSets->setSpacing(0);
    vblDefSets->addWidget(lbSelect);
    vblDefSets->addWidget(cbDefSets);
    vblDefSets->addWidget(pbNewPreset);
    vblDefSets->addWidget(pbDeletePreset);
    vblDefSets->addWidget(pbSavePreset);


    flPreSets->setSpacing(1);
    flPreSets->addRow(lbNewPreset->text(),leName);
    flPreSets->addRow(lbLen->text(), dsbLen);
    flPreSets->addRow(lbWid->text(), dsbWid);
    flPreSets->addRow(lbHei->text(), dsbHei);
    flPreSets->addRow(lbWei->text(), dsbWei);

    flLay->setSpacing(1);
    flLay->addRow(lbLay->text(), sbLayersNum);
    flLay->addRow(lbPcs->text(), sbPiecesNum);

    vhlVolume->addWidget(lbVolumeValue);
    vhlVolume->addWidget(lbVolumeUnit);

    vblPanel->addWidget(gbMng);
    vblPanel->addWidget(gbSetPresets);
    vblPanel->addWidget(gbLayers);
    vblPanel->addWidget(gbPosDir);
    vblPanel->addWidget(gbRestDir);
    vblPanel->addWidget(gbVolume);

    pbDeletePreset->setDisabled(checkBtnDisabled());

    connect(dsbLen, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=] () {
        lbVolumeValue->setText(calcVolume());
    });
    connect(dsbWid, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=] () {
       lbVolumeValue->setText(calcVolume());
    });
    connect(dsbHei, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=] () {
       lbVolumeValue->setText(calcVolume());
    });

    connect(pbNewPreset, &QPushButton::clicked, [=]{
       cbDefSets->setCurrentIndex(-1);
       leName->setDisabled(false);

       dsbLen->setDisabled(false);
       dsbLen->setValue(0);
       dsbHei->setDisabled(false);
       dsbHei->setValue(0);
       dsbWid->setDisabled(false);
       dsbWid->setValue(0);
       dsbWei->setDisabled(false);
       dsbWei->setValue(0);
       rbHorPos->setChecked(true);
       rbSideRest->setChecked(true);
       sbLayersNum->setDisabled(false);
       sbLayersNum->setValue(0);
       sbPiecesNum->setDisabled(false);
       sbPiecesNum->setValue(0);
       pbSavePreset->setDisabled(false);
    });

    connect(pbDeletePreset, &QPushButton::clicked, [=]{
        if (cbDefSets->currentText() == ""){
            QMessageBox::warning(this, "Cargo Ass.", "No preset selected!");
        }else{
            int a = QMessageBox::warning(this, "Cargo Ass.", "Delete the current preset?", QMessageBox::Yes | QMessageBox::No);
            if(a == QMessageBox::Yes){
                for (int i = 0; i < slPresets->count(); i++){
                    if (slPresets->at(i).contains(cbDefSets->currentText())){
                        slPresets->removeAt(i);
                        break;
                    }
                }
                QFile csv(sPath);
                if (csv.open(QIODevice::Append | QIODevice::Truncate | QIODevice::Text)){
                    for(int i = 0; i < slPresets->count(); ++i)
                    {
                        QTextStream ins(&csv);
                        ins << slPresets->at(i);
                    }
                }
                csv.close();
                cbDefSets->setCurrentIndex(-1);
                leName->setText("");
                dsbLen->setValue(0);
                dsbHei->setValue(0);
                dsbWid->setValue(0);
                dsbWei->setValue(0);
                sbLayersNum->setValue(0);
                sbPiecesNum->setValue(0);
                rbHorPos->setChecked(true);
                rbSideRest->setChecked(true);
                cbDefSets->clear();
                cbDefSets->addItems(loadNamesList());
            }
        }
        pbDeletePreset->setDisabled(checkBtnDisabled());
    });

    connect(pbSavePreset, &QPushButton::clicked, [=]{
             QString value = "";
            if (!checkIsValidValue(leName)){
                QMessageBox::warning(this, "Cargo Ass.", QString("Parameter ''%1'' not valid!").arg(lbNewPreset->text()));
                return;
            }
            if (!checkIsValidValue(dsbLen)){
                undoMsg(lbLen);
                return;
            }
            if (!checkIsValidValue(dsbWid)){
                undoMsg(lbWid);
                return ;
            }
            if (!checkIsValidValue(dsbHei)){
                undoMsg(lbHei);
                return ;
            }
            if (!checkIsValidValue(dsbWei)){
                undoMsg(lbWei);
                return ;
            }
            if (!checkIsValidValue(sbLayersNum)){
                undoMsg(lbLay);
                return ;
            }
            if (!checkIsValidValue(sbPiecesNum)){
                undoMsg(lbPcs);
                return ;
            }

            QFile csv(sPath);
            if (!fileExists()){ createPresetFile();}
            if (csv.open(QIODevice::Append | QIODevice::Text))
            {
                QTextStream ins(&csv);
                value = leName->text()+";"+
                        QString::number(dsbLen->value())+";"+
                        QString::number(dsbHei->value())+";"+
                        QString::number(dsbWid->value())+";"+
                        QString::number(dsbWei->value())+";"+
                        QString::number(sbLayersNum->value())+";"+
                        QString::number(sbPiecesNum->value())+";";
                if (rbHorPos->isChecked()){ value = value + QString::number(0)+";";}
                if (rbVertPos->isChecked()){ value = value + QString::number(1)+";";}
                if (rbPlaneRest->isChecked()){ value = value + QString::number(0)+";\n";}
                if (rbSideRest->isChecked()){ value = value + QString::number(1)+";\n";}
                value.replace(QLocale().decimalPoint(), QLatin1Char('.'));
                ins << value;
                slPresets->append(value);
                cbDefSets->clear();
                cbDefSets->addItems(loadNamesList());
                cbDefSets->setCurrentText(leName->text());
            };
            csv.close();
    }


);

    connect(cbDefSets, &QComboBox::currentTextChanged,[=](){
        for(int i = 0; i<slPresets->count(); i++)
        {
            if(slPresets->at(i).contains(cbDefSets->currentText())){
                QStringList slSplitedLine = slPresets->at(i).split(';');
                leName->setText(slSplitedLine.at(0));
                QString value = slSplitedLine.at(1);
                dsbLen->setValue(value.toDouble());
                value = slSplitedLine.at(2);
                dsbWid->setValue(value.toDouble());
                value = slSplitedLine.at(3);
                dsbHei->setValue(value.toDouble());
                value = slSplitedLine.at(4);
                dsbWei->setValue(value.toDouble());
                value = slSplitedLine.at(5);
                sbLayersNum->setValue(value.toInt());
                value = slSplitedLine.at(6);
                sbPiecesNum->setValue(value.toInt());
                rbHorPos->setChecked(slSplitedLine.at(7)=="0");
                rbVertPos->setChecked(slSplitedLine.at(7)=="1");
                rbPlaneRest->setChecked(slSplitedLine.at(8)=="0");
                rbSideRest->setChecked(slSplitedLine.at(8)=="1");

                break;
            }
        }
    });

}

double Panel::getCargoLenght()
{
    if (checkSelected()){
        return dsbLen->value();
    }
    else {
        return 0;
    }
}

double Panel::getCargoWidth()
{
    if (checkSelected()){
        return dsbWid->value();
    }
    else {
        return 0;
    }
}

double Panel::getCargoHeight()
{
    if (checkSelected()){
        return dsbHei->value();
    }
    else {
        return 0;
    }
}

double Panel::getCargoVolume()
{
    if (checkSelected()){
        QString v = lbVolumeValue->text();
        v.replace(QLocale().decimalPoint(), QLatin1Char('.'));
        return  v.toDouble();
    }
    else {
        return 0;
    }
}

double Panel::getCargoWeight()
{
    if (checkSelected()){
        return dsbWei->value();
    }
    else {
        return 0;
    }
}

int Panel::getLayers()
{
    return sbLayersNum->value();
}

int Panel::getLayerPieces()
{
    return sbPiecesNum->value();
}



bool Panel::checkSelected()
{
    return cbDefSets->currentIndex() >= 0 ;
}



QString Panel::calcVolume()
{
    QString v = QString::number(dsbHei->value()*dsbLen->value()*dsbWid->value());
    return v.replace(QLatin1Char('.'),  QLocale().decimalPoint());
}

bool Panel::fileExists()
{
    QFileInfo fiCheckFile(sPath);
    return fiCheckFile.exists() && fiCheckFile.isFile();
}

void Panel::createPresetFile()
{
    QFile csv(sPath);
    if (csv.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&csv);
        out << csvTitle;
        csv.close();
    }
}

QStringList Panel::loadPresetList()
{
    QStringList slData = {};
    QFile csv(sPath);
    if (!fileExists()){
        createPresetFile();
    }
    if (csv.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!csv.atEnd())
        {
            slData.append(csv.readLine());
        }
        csv.close();
    }
    return slData;
}

QStringList Panel::loadNamesList()
{
    QStringList slData = {};
    QStringList slList = {};
    QString line = "";
    for (int i = 0; i < slPresets->count();++i)
    {
        if(!slPresets->at(i).contains("Name"))
        {
            line = slPresets->at(i);
            slData = line.split(';');
            slList.append(slData.at(0));
            slData.clear();
        }
    }
    return slList;
}

bool Panel::checkBtnDisabled()
{
    if ((cbDefSets->count() > 0))
    {
        return  false;
    }else {
        return  true ;
   }
}




