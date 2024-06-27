#include <Novice.h>
#include "mt.h"
#include <imgui.h>

const char kWindowTitle[] = "GC1A_03_オノセ_ユウカ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	AABB aabb1{
		.min{-0.5f, -0.5f, -0.5f},
		.max{0.0f, 0.0f, 0.0f},
	};

	AABB aabb2{
		.min{0.2f, 0.2f, 0.2f},
		.max{1.0f, 1.0f, 1.0f},
	};

	int32_t color = WHITE;

	Vector3 rotate = {};
	Vector3 translate = {};
	Vector3 cameraRotate = { 0.0f, 0.0f, 0.0f };
	Vector3 cameraTranslate = {0.0f, 0.0f, -9.49f };
	Vector3 cameraPosition = { 0,0,-5.0f };

	Matrix4x4 viewProjectionMatrix = {};
	Matrix4x4 viewportMatrix = {};
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		viewProjectionMatrix = MakeViewProjectionMatrix({ 1, 1, 1 }, rotate, translate, { 1, 1, 1 }, cameraRotate, cameraTranslate);
		viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		if (isCollision(aabb1, aabb2)) {
			color = RED;
		}
		else {
			color = WHITE;
		}


		ImGui::DragFloat3("aabb1.min.", &aabb1.min.x, 0.01f);
		ImGui::DragFloat3("aabb1.max.", &aabb1.max.x, 0.01f);
		ImGui::DragFloat3("aabb2.min.", &aabb2.min.x, 0.01f);
		ImGui::DragFloat3("aabb2.max.", &aabb2.max.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);
		
		aabb1.min.x = (std::min)(aabb1.min.x, aabb1.max.x);
		aabb1.max.x = (std::max)(aabb1.min.x, aabb1.max.x);
		aabb1.min.y = (std::min)(aabb1.min.y, aabb1.max.y);
		aabb1.max.y = (std::max)(aabb1.min.y, aabb1.max.y);
		aabb1.min.z = (std::min)(aabb1.min.z, aabb1.max.z);
		aabb1.max.z = (std::max)(aabb1.min.z, aabb1.max.z);
		aabb2.min.x = (std::min)(aabb2.min.x, aabb2.max.x);
		aabb2.max.x = (std::max)(aabb2.min.x, aabb2.max.x);
		aabb2.min.y = (std::min)(aabb2.min.y, aabb2.max.y);
		aabb2.max.y = (std::max)(aabb2.min.y, aabb2.max.y);
		aabb2.min.z = (std::min)(aabb2.min.z, aabb2.max.z);
		aabb2.max.z = (std::max)(aabb2.min.z, aabb2.max.z);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);
		DrawAABB(aabb1, viewProjectionMatrix, viewportMatrix, color);
		DrawAABB(aabb2, viewProjectionMatrix, viewportMatrix, WHITE);

		/// 
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
