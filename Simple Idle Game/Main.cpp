# include <Siv3D.hpp> // Siv3D v0.6.16
# include "GameData.h"

void Main()
{
	const Texture cookie(U"🍪"_emoji);
	const Texture grandma(U"👵"_emoji);
	const Font font{ FontMethod::MSDF, 24, Typeface::Bold };

	const Circle cookieButton{ 400, 300, 100 };

	GameData data;
	// for the bounce effect
	double cookieScale = 1.5;

	while (System::Update()) {
		const double deltaTime = Scene::DeltaTime();
		if (cookieButton.mouseOver()) {
			// Cursor changes to hand when hovering over the cookie button
			Cursor::RequestStyle(CursorStyle::Hand);
		}
		if (cookieButton.leftClicked()) {
			// Increase cookies by 1 when the cookie button is clicked
			data.cookies += 1;
			// Bounce effect
			cookieScale = 1.25;
		}
		// Return the cookie scale to its original size over time
		cookieScale = Min((cookieScale + deltaTime), 1.5);

		// Draw the cookie button
		cookie.scaled(cookieScale).drawAt(cookieButton.center);

		// Draw the number of cookies
		font(U"Cookies: {}"_fmt(static_cast<long long>(data.cookies))).draw(50, 50);
		// Draw the number of grandmas
		font(U"Grandmas: {}"_fmt(data.grandma)).draw(50, 90);
		// Draw cookies per second
		font(U"Cookies per second: {}"_fmt(data.getCookiesPerSecond())).draw(50, 130);

		// Caculate cookies gained from grandmas
		data.cookies += data.getCookiesPerSecond() * deltaTime;

		// Draw the grandma buy button
		const Rect grandmaButton{ 50, 500, 350, 50 };
		if (grandmaButton.mouseOver()) {
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		// Draw button background
		grandmaButton.draw(ColorF(0.5, 0.5, 0.5));
		grandmaButton.drawFrame(2, 0, ColorF(0.8, 0.8, 0.8));
		
		// Draw the grandma button text
		font(U"Buy Grandma (10 cookies)").draw(grandmaButton.center().movedBy(-150, -20));
		font(U"Owned: {}"_fmt(data.grandma)).draw(grandmaButton.center().movedBy(-145, 30));

		// Handle grandma button click
		if (grandmaButton.leftClicked() && data.cookies >= 10) {
			data.cookies -= 10;
			data.grandma += 1;
		}
	}
}
