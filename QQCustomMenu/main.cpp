#include "QQCustomMenu.h"
#include <QtWidgets/QApplication>

#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QQCustomMenu w;
	w.addMenuItem(QIcon(":/Resources/busy.png"), "忙碌");
	w.addMenuItem(QIcon(":/Resources/hide.png"), "隐身");
	w.addMenuItem(QIcon(":/Resources/lock.png"), "锁定");
	w.addSeparator();
	w.addMenuItem(QIcon(":/Resources/offLine.png"), "离线");
	w.addMenuItem(QIcon(":/Resources/message.png"), "消息");
	w.show();
	return a.exec();
}
