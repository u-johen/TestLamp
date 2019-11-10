#include "formcoloroperator.h"
#ifndef FOMPAINEXEC_H
#define FOMPAINEXEC_H


class FormPaintExec : public FormColorOperator
{

  public:
    FormPaintExec(QMainWindow* ngdWindow);

    void Execute( QByteArray* readedData, quint16 dataLen);

};

#endif // FOMPAINEXEC_H
