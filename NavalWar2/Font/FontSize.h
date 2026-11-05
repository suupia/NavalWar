#pragma once

/// @brief 解像度に応じたフォントサイズを提供するユーティリティクラス
class FontSize
{
public:
	/// @brief キー値に応じたフォントサイズを取得します
	/// @param key フォントサイズの種別キー (0: 小, 1: 中, 2: 大)
	/// @return フォントサイズ (px)
	static int32 GetFontSize(int32 key);
};
