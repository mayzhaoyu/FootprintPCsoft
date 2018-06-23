#include "mQLabel.h"

mQLabel::mQLabel(QWidget *parent)
	: QLabel(parent)
{


}

mQLabel::~mQLabel()
{

}

void mQLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
	emit Doubleclicked();
}