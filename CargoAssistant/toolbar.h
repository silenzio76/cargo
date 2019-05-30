#ifndef TOOLBAR_H
#define TOOLBAR_H
#include <QString>
#include <QToolBar>
#include <QTableWidget>
#include <QTranslator>


class ToolBar : public QToolBar
{
    Q_OBJECT
    Q_PROPERTY(QString m_planeName READ planeName WRITE setPlaneName NOTIFY planeChanged )
public:
    explicit ToolBar(QWidget *parent, QString picsPath);
    void setImageFolderPath(QString Path);
    QString imageFolderPath = "";
    void setPicsPath(QString path);
    void setPresetWidget(QWidget * panel);
    void drawGrid(QStringList sl);
    void drawTree(QStringList sl);
    void setGridObj(QTableWidget *table);
    void setPlaneName(QString name);
    QString planeName();
signals:
    void planeChanged();
protected:
    QWidget *m_panel;
    QTableWidget *m_table;
    QString m_planeName;
protected slots:

private slots:
private:
    void addQuitButton(QWidget * Window);
    void addLoadDataButton(QWidget * Window, QTableWidget *t);
    void addDrawAreaButton(QWidget * Window);
    void addLanguageButton(QWidget * Window);
    void loadLanguage(const QString& sLanguage);
    void createLanguageMenu(void);
    QString m_imageFolderPath;



 };
#endif // TOOLBAR_H
