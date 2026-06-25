#include "DxLib.h"

static int _key, _trigger, _release;

int MouseTrigger()
{
	int keyold = _key;
	_key = GetMouseInput();
	// トリガ入力、リリース情報を生成する
	return _trigger = (_key ^ keyold) & _key;	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）
	//_release = (_key ^ keyold) & ~_key;	// キーのリリース情報生成（離した瞬間しか反応しないキー情報）
}