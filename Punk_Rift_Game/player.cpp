/*
 * Author: Jonathan Baird
 * Date: 1/29/2017
 * Purpose: MVC SEC Video Game Punk Rift
*/


#include "player.h"
#include <QDebug>
#include <QPainter>

Player::Player(QGraphicsItem *parent): QGraphicsItem(parent),m_direction(),mCurrentFrame(0), mState(Standing) {


    setFlag(ItemClipsToShape);
    mWalkPixmap = QPixmap(":images/sn4.png");
    mStandingPixmap = QPixmap(":images/stopf.png");
    mJumpPixmap = QPixmap(":images/jump.png");
    mPixmap = mWalkPixmap;
}

Player::~Player(){

}

void Player::stand() {
    mPixmap = mStandingPixmap;
    mCurrentFrame = 0;
    mState = Standing;

}

void Player::jump() {
    mState = Jumping;
}

void Player::walk() {
    //qDebug() << "Walking..";
    if(mState == Walking) {
        return;
    }

    mPixmap = mWalkPixmap;
    mCurrentFrame = 0;
    mState = Walking;
}

void Player::fall() {
    mState = Falling;
}

bool Player::isFalling() {
    return mState == Falling;
}

int Player::direction() const {
    return m_direction;
}

void Player::nextFrame() {
    mCurrentFrame += 148;
    if (mCurrentFrame >= 3108 ) {
        mCurrentFrame = 0;
    }
}

QRectF Player::boundingRect() const {
    return QRectF(0,0,140,161);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,140, 161);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

void Player::addDirection(int direction) {

    if (direction == m_direction)
        return;

    m_direction += direction;

    if (0 != m_direction) {
        if (-1 == m_direction)
            //QTransform matrix flips the image to face the other direction if left key is pressed
            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        else//moving right restore normal state by assigning an empty Qtransform object which is an idetntity matrix
            setTransform(QTransform());
    }
}

bool Player::isTouchingFoot(QGraphicsItem *item) {

    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) -5, boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}

bool Player::isTouchingHead(QGraphicsItem *item) {

    QRectF rect(pos().x(), pos().y(), boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());   
    return rect.intersects(otherRect);
}

bool Player::isTouchingPlatform(QGraphicsItem *item) {
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 5, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());

    return rect.intersects(otherRect);
}

