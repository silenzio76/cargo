#ifndef QGLOBALEVENTFILTER_H
#define QGLOBALEVENTFILTER_H

#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include <QApplication>

class QGlobalEventFilter : public QObject
{
public:
    explicit QGlobalEventFilter(QObject *parent) : QObject(parent) {}
    bool eventFilter(QObject *obj, QEvent *ev) override {
        if (ev->type() == QEvent::KeyPress || ev->type() == QEvent::KeyRelease) {
            QKeyEvent *kev = static_cast<QKeyEvent *>(ev);
            if (kev->key() == Qt::Key_Period && (kev->modifiers() & Qt::KeypadModifier)) {
                QChar decimalPoint = QLocale().decimalPoint();
                if (decimalPoint == QLatin1Char(',')) {
                    QKeyEvent modifiedKeyEvent(kev->type(), Qt::Key_Comma, kev->modifiers(), QString(decimalPoint), kev->isAutoRepeat(), kev->count());
                    qApp->sendEvent(obj, &modifiedKeyEvent);
                    return true;
                }
            }
        return false;
    }
  }
};

#endif // QGLOBALEVENTFILTER_H
