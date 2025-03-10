/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 https://adxeproject.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "Ball.h"
#include "Paddle.h"
#include "../VisibleRect.h"

USING_NS_CC;

Ball::Ball() {}

Ball::~Ball() {}

float Ball::radius()
{
    return getTexture()->getContentSize().width / 2;
}

Ball* Ball::ballWithTexture(Texture2D* aTexture)
{
    Ball* pBall = new Ball();
    pBall->initWithTexture(aTexture);
    pBall->autorelease();

    return pBall;
}

void Ball::move(float delta)
{
    this->setPosition(getPosition() + _velocity * delta);

    if (getPosition().x > VisibleRect::right().x - radius())
    {
        setPosition(VisibleRect::right().x - radius(), getPosition().y);
        _velocity.x *= -1;
    }
    else if (getPosition().x < VisibleRect::left().x + radius())
    {
        setPosition(VisibleRect::left().x + radius(), getPosition().y);
        _velocity.x *= -1;
    }
}

void Ball::collideWithPaddle(Paddle* paddle)
{
    auto paddleRect = paddle->getRect();
    paddleRect.origin.x += paddle->getPosition().x;
    paddleRect.origin.y += paddle->getPosition().y;

    float lowY  = paddleRect.getMinY();
    float midY  = paddleRect.getMidY();
    float highY = paddleRect.getMaxY();

    float leftX  = paddleRect.getMinX();
    float rightX = paddleRect.getMaxX();

    if (getPosition().x > leftX && getPosition().x < rightX)
    {

        bool hit          = false;
        float angleOffset = 0.0f;

        if (getPosition().y > midY && getPosition().y <= highY + radius())
        {
            setPosition(getPosition().x, highY + radius());
            hit         = true;
            angleOffset = (float)M_PI / 2;
        }
        else if (getPosition().y < midY && getPosition().y >= lowY - radius())
        {
            setPosition(getPosition().x, lowY - radius());
            hit         = true;
            angleOffset = -(float)M_PI / 2;
        }

        if (hit)
        {
            float hitAngle = (paddle->getPosition() - getPosition()).getAngle() + angleOffset;

            float scalarVelocity = _velocity.getLength() * 1.05f;
            float velocityAngle  = -_velocity.getAngle() + 0.5f * hitAngle;

            _velocity = Vec2::forAngle(velocityAngle) * scalarVelocity;
        }
    }
}
