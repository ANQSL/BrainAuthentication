#include "monitorconfigwidget.h"
#include "ui_monitorconfigwidget.h"
#include "QStyleOptionTab"
#include "QPainter"
MonitorConfigWidget::MonitorConfigWidget(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::MonitorConfigWidget)
{
    ui->setupUi(this);
    tabwidget=new QTabWidget;
    ui->widget_layout->addWidget(tabwidget);
    this->tabwidget->tabBar()->setStyle(new CustomTabStyle);
    this->tabwidget->setTabPosition(QTabWidget::West);
}

MonitorConfigWidget::~MonitorConfigWidget()
{
    delete ui;
}

void MonitorConfigWidget::addConfigWidget(QWidget *widget, QString name)
{
    this->tabwidget->addTab(widget,name);
}

QSize CustomTabStyle::sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const
{
    QSize s=QProxyStyle::sizeFromContents(type,option,size,widget);
        if(type==QStyle::CT_TabBarTab){
            s.transposed();
            s.rwidth()=100;
            s.rheight()=50;
        }
        return s;
}

void CustomTabStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    if(element==CE_TabBarTabLabel){
    if(const QStyleOptionTab *tab=qstyleoption_cast<const QStyleOptionTab *>(option))
    {
        QRect allRect=tab->rect;
        if(tab->state&QStyle::State_Selected){
            painter->save();
            painter->setPen(0x89cfff);
            painter->setBrush(QBrush(0x89cfff));
            painter->drawRect(allRect.adjusted(6,6,-6,-6));
            painter->restore();
        }
        QTextOption option;
        option.setAlignment(Qt::AlignCenter);
        if(tab->state&QStyle::State_Selected){
            painter->setPen(0xf8fcff);
        }else{
            painter->setPen(0x000001);
        }
        painter->drawText(allRect,tab->text,option);
        return ;
    }
    }
    if(element==CE_TabBarTab){
        QProxyStyle::drawControl(element,option,painter,widget);
    }
}
