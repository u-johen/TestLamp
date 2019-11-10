#include "formcoloroperator.h"


void FormColorOperator::SetColorToMW(QColor clrForSet)
{
    QPalette palette = (*mW).palette();
    palette.setColor(QPalette::Background,clrForSet);
    (*mW).setPalette(palette);
}
