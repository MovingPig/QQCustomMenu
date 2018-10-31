#ifndef QQ_CUSTOM_MENU_H
#define QQ_CUSTOM_MENU_H

/**
* @author : 前行中的小猪;
* @date   : 2018年05月18日
* @version: 1.0
* @note   : 模仿QQ菜单样式，实现自定义菜单，通过ListWidget加载菜单项;
			1、自动设置菜单高度，根据当前添加的菜单项自增菜单高度;
			2、菜单宽度可根据菜单文字自行设置;
			3、菜单的透明度、菜单边框阴影宽度、菜单四角圆角弧度均可设置;
			4、其他菜单等样式，菜单项文字颜色，图标等均可自行设置，
			   这里只给出一个模板，大家可自行发挥拓展;

*@ 博客地址: https://blog.csdn.net/GoForwardToStep ;
**/


#include <QtWidgets/QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QIcon>
#include <QPainter>
#include <QListWidget>

#define MENU_ITEM_HEIGHT 30			// 菜单项的高度;

class QQMenuItemWidget : public QWidget
{
	Q_OBJECT

public:
	QQMenuItemWidget()
		: m_isEnter(false)
		, m_itemIndex(0)
	{
		m_iconLabel = new QLabel;
		m_iconLabel->setFixedSize(QSize(20, 20));

		m_textLabel = new QLabel;
		m_textLabel->setStyleSheet("font-family:Microsoft YaHei;font-size:14px;");

		QHBoxLayout* hLayout = new QHBoxLayout(this);
		hLayout->addWidget(m_iconLabel);
		hLayout->addWidget(m_textLabel);
		hLayout->addStretch();
		hLayout->setSpacing(10);
		hLayout->setContentsMargins(10, 0, 0, 0);

		this->setFixedHeight(MENU_ITEM_HEIGHT);
		this->setAttribute(Qt::WA_TranslucentBackground);
	}

	// 设置菜单项文字;
	void setMenuItemText(const QString& text)
	{
		m_textLabel->setText(text);
		m_textLabel->setScaledContents(true);
	}
	
	// 设置菜单项图标;
	void setMenuItemIcon(const QIcon& icon)
	{
		m_iconLabel->setPixmap(icon.pixmap(QSize(20, 20)));
	}

	// 设置菜单项Index;
	void SetMenuItemIndex(const int& index)
	{
		m_itemIndex = index;
	}

private:
	void mouseReleaseEvent(QMouseEvent *event)
	{
		emit signalMenuClicked(m_itemIndex);
	}

	void enterEvent(QEvent *event)
	{
		m_isEnter = true;
		update();
	}

	void leaveEvent(QEvent *event)
	{
		m_isEnter = false;
		update();
	}

	void paintEvent(QPaintEvent *event)
	{
		if (m_isEnter)
		{
			QPainter painter(this);
			painter.fillRect(this->rect(), QColor(215, 215, 215, 150));
		}
	}

signals:
	// 通知菜单项被点击;
	void signalMenuClicked(int);

private:
	QLabel* m_iconLabel;
	QLabel* m_textLabel;
	int m_itemIndex;
	bool m_isEnter;
};

class QQCustomMenu : public QWidget
{
	Q_OBJECT

public:
	QQCustomMenu(QWidget *parent = Q_NULLPTR);
	// 添加菜单项;
	void addMenuItem(const QIcon &icon, const QString &text);
	// 添加分隔项;
	void addSeparator();

private:
	void initWidget();
	void paintEvent(QPaintEvent *event);

private slots:
	// 根据Index判断当前点击了那个菜单项;
	void onMenuItemClicked(int menuItemIndex);

private:
	QListWidget* m_menuItemListWidget;
	// 根据当前添加的菜单项和分隔项自动计算菜单高度;
	int m_currentMenuHeight;
	// 记录菜单项Index;
	int m_menuItemIndex;
};
#endif