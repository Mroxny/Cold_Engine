#include "KeyboardManager.h"

bool KeyboardManager::KeyIsPressed(unsigned char keycode) const noexcept
{
	return keystates[keycode];
}

std::optional<KeyboardManager::Event> KeyboardManager::ReadKey() noexcept
{
	if (keybuffer.size() > 0u)
	{
		KeyboardManager::Event e = keybuffer.front();
		keybuffer.pop();
		return e;
	}
	return {};
}

bool KeyboardManager::KeyIsEmpty() const noexcept
{
	return keybuffer.empty();
}

std::optional<char> KeyboardManager::ReadChar() noexcept
{
	if (charbuffer.size() > 0u)
	{
		unsigned char charcode = charbuffer.front();
		charbuffer.pop();
		return charcode;
	}
	return {};
}

bool KeyboardManager::CharIsEmpty() const noexcept
{
	return charbuffer.empty();
}

void KeyboardManager::ClearKey() noexcept
{
	keybuffer = std::queue<Event>();
}

void KeyboardManager::ClearChar() noexcept
{
	charbuffer = std::queue<char>();
}

void KeyboardManager::Clear() noexcept
{
	ClearKey();
	ClearChar();
}

void KeyboardManager::EnableAutorepeat() noexcept
{
	autorepeatEnabled = true;
}

void KeyboardManager::DisableAutorepeat() noexcept
{
	autorepeatEnabled = false;
}

bool KeyboardManager::AutorepeatIsEnabled() const noexcept
{
	return autorepeatEnabled;
}

//Private section (Win API)

void KeyboardManager::OnKeyPressed(unsigned char keycode) noexcept
{
	keystates[keycode] = true;
	keybuffer.push(KeyboardManager::Event(KeyboardManager::Event::Type::Press, keycode));
	TrimBuffer(keybuffer);
}

void KeyboardManager::OnKeyReleased(unsigned char keycode) noexcept
{
	keystates[keycode] = false;
	keybuffer.push(KeyboardManager::Event(KeyboardManager::Event::Type::Release, keycode));
	TrimBuffer(keybuffer);
}

void KeyboardManager::OnChar(char character) noexcept
{
	charbuffer.push(character);
	TrimBuffer(charbuffer);
}

void KeyboardManager::ClearState() noexcept
{
	keystates.reset();
}

template<typename T>
void KeyboardManager::TrimBuffer(std::queue<T>& buffer) noexcept
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}