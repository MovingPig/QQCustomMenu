#include "QQCustomMenu.h"
#include <QPainter>
#include <QGraphicsDropShadowEffect>

#define SHADOW_WIDTH 15					// 窗口阴影宽度;
#define WINDOW_WIDTH 180				// 菜单宽度;
#define SEPARATOR_HEIGHT 12				// 分割线高度;
#define VMARGIN 10						// QListWidget纵向的边距;
#define BORDER_RADIUS 5					// 菜单四角圆角的弧度;
#define WINDPW_OPACITY 0.9				// 菜单背景透明度;

QQCustomMenu::QQCustomMenu(QWidget *parent)
	: QWidget(parent)
	, m_menuItemIndex(0)
{
	initWidget();

	// 设置窗户属性;
	setWindowFlags(Qt::FramelessWindowHint/* | Qt::Tool*/);		// 正式应用时要加上 Qt::Tool;
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowOpacity(WINDPW_OPACITY);
	setFixedWidth(WINDOW_WIDTH);
	setStyleSheet("QListView{border:none} QListView::item{background:transparent;}");

	// 设置阴影边框;
	auto shadowEffect = new QGraphicsDropShadowEffect(this);
	shadowEffect->setOffset(0, 0);
	shadowEffect->setColor(Qt::gray);
	shadowEffect->setBlurRadius(SHADOW_WIDTH);
	this->setGraphicsEffect(shadowEffect);

	// 计算默认高度;
	m_currentMenuHeight = SHADOW_WIDTH * 2 + VMARGIN * 2;
	this->setFixedHeight(m_currentMenuHeight);
}

void QQCustomMenu::initWidget()
{
	m_menuItemListWidget = new QListWidget;
	m_menuItemListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_menuItemListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	QHBoxLayout* hMainLayout = new QHBoxLayout(this);
	hMainLayout->addWidget(m_menuItemListWidget);
	hMainLayout->setContentsMargins(SHADOW_WIDTH, SHADOW_WIDTH + VMARGIN, SHADOW_WIDTH, SHADOW_WIDTH + VMARGIN);
}

void QQCustomMenu::addMenuItem(const QIcon &icon, const QString &text)
{
	QQMenuItemWidget* menuItem = new QQMenuItemWidget;
	menuItem->setMenuItemIcon(icon);
	menuItem->setMenuItemText(text);
	connect(menuItem, &QQMenuItemWidget::signalMenuClicked, this, &QQCustomMenu::onMenuItemClicked);

	QListWidgetItem* item = new QListWidgetItem;
	item->setSizeHint(QSize(WINDOW_WIDTH - 2 * SHADOW_WIDTH, MENU_ITEM_HEIGHT));
	m_menuItemListWidget->addItem(item);
	m_menuItemListWidget->setItemWidget(item, menuItem);

	m_menuItemIndex++;
	m_currentMenuHeight += MENU_ITEM_HEIGHT;
	this->setFixedHeight(m_currentMenuHeight);
}

void QQCustomMenu::addSeparator()
{
	QFrame* separatorLabel = new QFrame;
	separatorLabel->setFrameShape(QFrame::HLine);
	separatorLabel->setLineWidth(1);
	separatorLabel->setFrameShadow(QFrame::Sunken);
	// 设置分隔线颜色;
	QPalette palette = separatorLabel->palette();
	palette.setColor(QPalette::Dark, QColor(219, 219, 219, 150));
	separatorLabel->setPalette(palette);

	QListWidgetItem* item = new QListWidgetItem;
	item->setSizeHint(QSize(WINDOW_WIDTH - 2 * SHADOW_WIDTH, SEPARATOR_HEIGHT));
	m_menuItemListWidget->addItem(item);
	m_menuItemListWidget->setItemWidget(item, separatorLabel);

	m_currentMenuHeight += SEPARATOR_HEIGHT;
	this->setFixedHeight(m_currentMenuHeight);
}

void QQCustomMenu::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::white);
	painter.drawRoundedRect(QRect(SHADOW_WIDTH, SHADOW_WIDTH, \
		width() - SHADOW_WIDTH * 2, height() - SHADOW_WIDTH * 2), BORDER_RADIUS, BORDER_RADIUS);
}

void QQCustomMenu::onMenuItemClicked(int menuItemIndex)
{
	// 根据点击不同的菜单项进行不同操作，这里应发出信号去通知调用菜单的widget;
}