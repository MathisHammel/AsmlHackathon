#include "paletteeditor.h"

#include <QPainter>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>

PaletteEditor::PaletteEditor(QWidget* parent):
    QWidget(parent)
{
    m_model = vector<vector<bool>>(m_rows, vector<bool>(m_columns, false));

    m_penRed = QPen(QBrush(Qt::black), 1);
}

QSize PaletteEditor::sizeHint() const{
    return QSize(500, 500);
}

int PaletteEditor::boxSize()
{
    return width()/32;
}

void PaletteEditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int size = boxSize();

    painter.setPen(m_penRed);

    for (int r = 0; r < m_rows; ++r){
        for (int c = 0; c < m_columns; ++c){
            int posY = r*size;
            int posX = c*size;;

            painter.setBrush(QBrush((m_model[r][c] ? Qt::red : Qt::transparent)));
            painter.drawRect(QRectF(posX, posY, size, size));
        }
    }
}

void PaletteEditor::drawAtPixel(const QPoint& pos, bool value){
    int x = pos.x();
    int y = pos.y();

    int rHeight = m_columns*width()/32;

    int c = x/boxSize();
    int r = y/boxSize();

    if (c >= 32)
        return;
    if (r >= 32)
        return;

    m_model[r][c] = value;

    m_lastR = r;
    m_lastC = c;

    update();
}

void PaletteEditor::swapAtPixel(const QPoint& pos, bool trackSame){

    int x = pos.x();
    int y = pos.y();

    int rHeight = m_columns*width()/32;

    int c = x/boxSize();
    int r = y/boxSize();

    if (trackSame && m_lastC == c && m_lastR == r)
        return;

    if (c >= 32)
        return;
    if (r >= 32)
        return;

    m_model[r][c] = !m_model[r][c];

    m_lastR = r;
    m_lastC = c;

    update();
}

void PaletteEditor::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton)
        swapAtPixel(event->pos(), false);
}

void PaletteEditor::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
        drawAtPixel(event->pos(), true);
    else if (event->buttons() & Qt::RightButton)
        drawAtPixel(event->pos(), false);
}

void PaletteEditor::clear(){
    m_model = vector<vector<bool>>(m_rows, vector<bool>(m_columns, false));
    update();
}
