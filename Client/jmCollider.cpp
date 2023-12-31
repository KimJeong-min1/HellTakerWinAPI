#include "jmCollider.h"
#include "jmTransform.h"
#include "jmGameObject.h"

namespace jm
{
	UINT Collider::mCollisionCount = 0;

	Collider::Collider()
		:Component(eComponentType::Collider)
		,mSize(Vector2::zero)
		,mOffset(Vector2::zero)
		,mCollisionNumber(-1)
		,mbIsCollision(false)
	{
		mCollisionNumber = mCollisionCount;
		mCollisionCount++;
	}
	Collider::~Collider()
	{
	}
	void Collider::Initialize()
	{
	}
	void Collider::Update()
	{
	}
	void Collider::Render(HDC hdc)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		mPosition = pos + mOffset;

		pos.x -= mSize.x / 2.0f;
		pos.y -= mSize.y / 2.0f;
		pos.x += mOffset.x;
		pos.y += mOffset.y;

		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, transparentBrush);

		HPEN pen = NULL;
		if (mbIsCollision)
		{
			pen = CreatePen(PS_SOLID, 2, RGB(255, 50, 50));
		}
		else 
		{
			pen = CreatePen(PS_SOLID, 2, RGB(50, 255, 50));
		}
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		Rectangle(hdc, pos.x, pos.y, pos.x + mSize.x, pos.y + mSize.y);

		SelectObject(hdc, oldbrush);
		DeleteObject(transparentBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(pen);
	}
	void Collider::OnCollisionEnter(Collider* other)
	{
		mbIsCollision = true;
		GetOwner()->OnCollisionEnter(other);
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}
	void Collider::OnCollisionExit(Collider* other)
	{
		mbIsCollision = false;
		GetOwner()->OnCollisionExit(other);
	}
}