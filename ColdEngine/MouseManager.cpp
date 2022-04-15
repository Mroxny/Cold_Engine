#include "CE_Win.h"
#include "MouseManager.h"


std::pair<int, int> MouseManager::GetPos() const noexcept
{
	return { x,y };
}

std::optional<MouseManager::RawDelta> MouseManager::ReadRawDelta() noexcept
{
	if (rawDeltaBuffer.empty())
	{
		return std::nullopt;
	}
	const RawDelta d = rawDeltaBuffer.front();
	rawDeltaBuffer.pop();
	return d;
}

int MouseManager::GetPosX() const noexcept
{
	return x;
}

int MouseManager::GetPosY() const noexcept
{
	return y;
}

bool MouseManager::IsInWindow() const noexcept
{
	return isInWindow;
}

bool MouseManager::LeftIsPressed() const noexcept
{
	return leftIsPressed;
}

bool MouseManager::RightIsPressed() const noexcept
{
	return rightIsPressed;
}

std::optional<MouseManager::Event> MouseManager::Read() noexcept
{
	if (buffer.size() > 0u)
	{
		MouseManager::Event e = buffer.front();
		buffer.pop();
		return e;
	}
	return {};
}

void MouseManager::Clear() noexcept
{
	buffer = std::queue<Event>();
}

void MouseManager::EnableRaw() noexcept
{
	rawEnabled = true;
}

void MouseManager::DisableRaw() noexcept
{
	rawEnabled = false;
}

bool MouseManager::RawEnabled() const noexcept
{
	return rawEnabled;
}

void MouseManager::OnMouseMove(int newx, int newy) noexcept
{
	x = newx;
	y = newy;

	buffer.push(MouseManager::Event(MouseManager::Event::Type::Move, *this));
	TrimBuffer();
}

void MouseManager::OnMouseLeave() noexcept
{
	isInWindow = false;
	buffer.push(MouseManager::Event(MouseManager::Event::Type::Leave, *this));
	TrimBuffer();
}

void MouseManager::OnMouseEnter() noexcept
{
	isInWindow = true;
	buffer.push(MouseManager::Event(MouseManager::Event::Type::Enter, *this));
	TrimBuffer();
}

void MouseManager::OnRawDelta(int dx, int dy) noexcept
{
	rawDeltaBuffer.push({ dx,dy });
	TrimBuffer();
}

void MouseManager::OnLeftPressed(int x, int y) noexcept
{
	leftIsPressed = true;

	buffer.push(MouseManager::Event(MouseManager::Event::Type::LPress, *this));
	TrimBuffer();
}

void MouseManager::OnLeftReleased(int x, int y) noexcept
{
	leftIsPressed = false;

	buffer.push(MouseManager::Event(MouseManager::Event::Type::LRelease, *this));
	TrimBuffer();
}

void MouseManager::OnRightPressed(int x, int y) noexcept
{
	rightIsPressed = true;

	buffer.push(MouseManager::Event(MouseManager::Event::Type::RPress, *this));
	TrimBuffer();
}

void MouseManager::OnRightReleased(int x, int y) noexcept
{
	rightIsPressed = false;

	buffer.push(MouseManager::Event(MouseManager::Event::Type::RRelease, *this));
	TrimBuffer();
}

void MouseManager::OnWheelUp(int x, int y) noexcept
{
	buffer.push(MouseManager::Event(MouseManager::Event::Type::WheelUp, *this));
	TrimBuffer();
}

void MouseManager::OnWheelDown(int x, int y) noexcept
{
	buffer.push(MouseManager::Event(MouseManager::Event::Type::WheelDown, *this));
	TrimBuffer();
}

void MouseManager::TrimBuffer() noexcept
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}

void MouseManager::TrimRawInputBuffer() noexcept
{
	while (rawDeltaBuffer.size() > bufferSize)
	{
		rawDeltaBuffer.pop();
	}
}

void MouseManager::OnWheelDelta(int x, int y, int delta) noexcept
{
	wheelDeltaCarry += delta;
	// generate events for every 120 
	while (wheelDeltaCarry >= WHEEL_DELTA)
	{
		wheelDeltaCarry -= WHEEL_DELTA;
		OnWheelUp(x, y);
	}
	while (wheelDeltaCarry <= -WHEEL_DELTA)
	{
		wheelDeltaCarry += WHEEL_DELTA;
		OnWheelDown(x, y);
	}
}