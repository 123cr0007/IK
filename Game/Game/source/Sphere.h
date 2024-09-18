#pragma once

#include "appframe.h"
#include "ObjectBase.h"
#include <string>


class Sphere : public ObjectBase {
public:

    // インスタンスの生成
    static Sphere* SpherelInstance;
    static Sphere* GetSphereInstance() { return (Sphere*)SpherelInstance; }

    Sphere();

    bool Initialize()override;
    bool Terminate();
    bool Process()override;
    bool Render(int type) override;

    // フレームの番号から情報を取る
    void GetFrameInfoFromIndex(int chHandle, int index);
    // フレームの名前から情報を取る
    void GetFrameInfoFromName(int chHandle, const CHAR* name);

protected:

    // 3Dモデル描画用
    int ModelHandle;

    struct SphereInfo {
        VECTOR position;   // 位置
        MATRIX localMat;   // 回転行列
        float radius;      // 半径
        int color = GetColor(0, 0, 0);// 色
        int index;         // 球の番号
        bool isHit = false; // 当たり判定フラグ
    };
    // 球体の配列
    std::vector<SphereInfo> spheres;

    // 球体の初期化関数
    void initializeSpheres();
    // 球体の当たり判定関数
    void hitCheckSpheres();


    // マウスのX座標
    int mouseX;
    // マウスのY座標
    int mouseY;

    // 球の距離
    float sLengh;


    // キャラクターハンドル
	int charHandle;

    // マウスと球の距離
    float mouseSphereLengh;
    float oldMouseSphereLengh;

    VECTOR mouseWorldStartPos;	// マウスのワールド座標(カメラの一番奥)
    VECTOR mouseWorldEndPos;	// マウスのワールド座標(カメラの一番手前)
    VECTOR oldMousePos;			// マウスのワールド座標(カプセルと円錐の中間地点)
    VECTOR mouseLine;			// マウスのワールド座標(カメラの一番奥から一番手前までの直線)

    // デバッグ用
    VECTOR debugPos;
    VECTOR debugPos2;
    VECTOR debugPos3;

    float checkLengh;
    float checkLengh2;
};