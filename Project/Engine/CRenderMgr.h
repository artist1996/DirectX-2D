#pragma once

class CCamera;
class CGameObject;

class CRenderMgr
	: public CSingleton<CRenderMgr>
{
	SINGLE(CRenderMgr);
private:
	vector<CCamera*>		m_vecCam;
	list<tDebugShapeInfo>	m_DebugShapeList;

	CGameObject*			m_DebugObject;

public:
	void AddDebugShapeInfo(tDebugShapeInfo _Info) { m_DebugShapeList.push_back(_Info); }
	void RegisterCamera(CCamera* _Cam, int _CamPriority);

private:
	void RenderDebugShape();

public:
	void Init();
	void Tick();
};

