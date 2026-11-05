#pragma once

/// 解像度向けのフォントサイズをキーで返すユーティリティ。
class FontSize
{
public:
	/// キー 0, 1, 2 を小・中・大のフォントサイズ (px) に変換する。
	static int32 GetFontSize(int32 key);
};
