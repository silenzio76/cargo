#ifndef PANEL_H
#define PANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QKeyEvent>

class Panel : public QWidget
{
    Q_OBJECT
public:
    explicit Panel(QWidget *parent = nullptr);


    QLineEdit *leName;

    QComboBox *cbDefSets;


    QPushButton *pbLoadPreset;
    QPushButton *pbNewPreset;
    QPushButton *pbSavePreset;
    QPushButton *pbDeletePreset;

    QDoubleSpinBox *dsbLen;
    QDoubleSpinBox *dsbWid;
    QDoubleSpinBox *dsbHei;
    QDoubleSpinBox *dsbWei;
    QSpinBox *sbLayersNum;
    QSpinBox *sbPiecesNum;

    QRadioButton *rbVertPos;
    QRadioButton *rbHorPos;
    QRadioButton *rbPlaneRest;
    QRadioButton *rbSideRest;

    QLabel *lbVolumeValue;

    QStringList *slPresets = {};
    QStringList *slNames = {};
    QString sPath;


    const QString csvName = "Presets.csv";
    const QString csvTitle = "Name;Lenght;Width;Height;Weight;Pos;Rest;\n";

    double getCargoLenght();
    double getCargoWidth();
    double getCargoHeight();
    double getCargoVolume();
    double getCargoWeight();
    int getLayers();
    int getLayerPieces();
protected:

private slots:
private:
    bool checkSelected();
    QString calcVolume();
    bool fileExists();
    void createPresetFile();
    void addPreset();
    void savePresets();
    QStringList loadPresetList();
    QStringList loadNamesList();
    QStringList loadPreset(QString PresetName);
    void deletePreset(QString PresetName);
    bool checkBtnDisabled();

};


#endif // PANEL_H
