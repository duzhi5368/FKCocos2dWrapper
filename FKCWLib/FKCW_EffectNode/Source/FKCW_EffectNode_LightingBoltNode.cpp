//-------------------------------------------------------------------------
#include "../Include/FKCW_EffectNode_LightingBoltNode.h"
#include "../../FKCW_Base/Include/FKCW_Base_Utils.h"
//-------------------------------------------------------------------------
#pragma warning( disable:4244 )
#pragma warning( disable:4305 )
//-------------------------------------------------------------------------
const char* s_LightingBoltVerterShader = "	\n\
attribute vec4 a_position;					\n\
attribute vec2 a_texCoord;					\n\
attribute vec4 a_color;						\n\
varying vec2 v_texCoord;					\n\
varying vec4 v_color;						\n\
											\n\
void main()									\n\
{											\n\
	vec4 pos=vec4(a_position.xy,0,1);		\n\
	gl_Position = CC_MVPMatrix * pos;		\n\
	v_texCoord = a_texCoord;				\n\
	v_color = a_color;						\n\
}";
//-------------------------------------------------------------------------
const char* s_LightingBoltFragShader = "					\n\
#ifdef GL_ES												\n\
	precision mediump float;								\n\
#endif														\n\
															\n\
varying vec2 v_texCoord;									\n\
varying vec4 v_color;										\n\
uniform sampler2D CC_Texture0;								\n\
uniform float u_opacity;									\n\
															\n\
void main() {												\n\
	vec4 texColor=texture2D(CC_Texture0, v_texCoord);		\n\
	gl_FragColor=texColor*v_color*u_opacity;				\n\
}";
//-------------------------------------------------------------------------
FKCW_EffectNode_LightingSeg::FKCW_EffectNode_LightingSeg()
{
	_InitParameter();
}
//-------------------------------------------------------------------------
FKCW_EffectNode_LightingSeg::FKCW_EffectNode_LightingSeg(CCPoint start,CCPoint end)
{
	_InitParameter();
	init(start, end);
}
//-------------------------------------------------------------------------
FKCW_EffectNode_LightingSeg::~FKCW_EffectNode_LightingSeg()
{

}
//-------------------------------------------------------------------------
void FKCW_EffectNode_LightingSeg::_InitParameter()
{
	branchID=-1;
	branchStartGenerationID=-1;
	generationID=-1;
	father=NULL;
	needReGenerate=false;
}
//-------------------------------------------------------------------------
void FKCW_EffectNode_LightingSeg::init(CCPoint start,CCPoint end)
{
    startPoint=start;
    endPoint=end;
}
//-------------------------------------------------------------------------
bool FKCW_EffectNode_LightingSeg::addChildRef(FKCW_EffectNode_LightingSeg*child){
    // ����Ƿ���ڣ��������ظ����
    int nChild=(int)childList.size();
    for(int i=0;i<nChild;i++)
	{
        if(childList[i]==child)
		{
            return false;
        }
    }
    childList.push_back(child);
    return true;
}
//-------------------------------------------------------------------------
bool FKCW_EffectNode_LightingSeg::removeChildRef(FKCW_EffectNode_LightingSeg*child)
{
    // ��ɾ����һ��ƥ����ӽڵ�
    int nChild=(int)childList.size();
    for(int i=0;i<nChild;i++)
	{
        if(childList[i]==child)
		{
            childList.erase(childList.begin()+i);
            nChild--;
            i--;
            return true;
        }
    }
    return false;
}
//-------------------------------------------------------------------------
float FKCW_EffectNode_LightingSeg::getLen()const 
{
    return ccpDistance(startPoint, endPoint);
}
//-------------------------------------------------------------------------
CCPoint FKCW_EffectNode_LightingSeg::getDir()const 
{
    return ccpNormalize(endPoint-startPoint);
}
//-------------------------------------------------------------------------
CCPoint FKCW_EffectNode_LightingSeg::getVec()const 
{
    return endPoint-startPoint;
}
//-------------------------------------------------------------------------
CCPoint FKCW_EffectNode_LightingSeg::getRightNormal()const 
{
    CCPoint dir=getDir();
    CCPoint normal(dir.y,-dir.x);
    return normal;
}
//-------------------------------------------------------------------------
CCPoint FKCW_EffectNode_LightingSeg::getMidPoint()const 
{
    return ccpMidpoint(startPoint, endPoint);
}
//-------------------------------------------------------------------------
// FKCW_EffectNode_LightingBoltSprite
//-------------------------------------------------------------------------
FKCW_EffectNode_LightingBoltSprite::FKCW_EffectNode_LightingBoltSprite()
{
	m_mainSegLen=14;
	m_k_offset=0.13;
	updateNGeneration();
	m_headSeg=NULL;
	m_tailSeg=NULL;
	m_program=NULL;
	m_indexVBO=NULL;
	m_isDrawDebug=false;
	m_percentageOfJitterBranch=0.5;
	m_opacityZoom=1.2;
	m_mesh=NULL;
}
//-------------------------------------------------------------------------
FKCW_EffectNode_LightingBoltSprite::~FKCW_EffectNode_LightingBoltSprite()
{
	int nseg=(int)m_segList.size();
	for(int i=0;i<nseg;i++)
	{
		if(m_segList[i]!=NULL)
		{
			delete m_segList[i];
			m_segList[i]=NULL;
		}
	}
	if(m_program)m_program->release();
	if(m_indexVBO)m_indexVBO->release();
	if(m_mesh)m_mesh->release();
}
//-------------------------------------------------------------------------
void FKCW_EffectNode_LightingBoltSprite::initProgram()
{
    // ��ʼ��shader
    FKCW_EffectNode_GLProgramWithUnifos* pProgram = new FKCW_EffectNode_GLProgramWithUnifos();
    pProgram->autorelease();
    pProgram->initWithVertexShaderByteArray(s_LightingBoltVerterShader, s_LightingBoltFragShader);
    pProgram->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    pProgram->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    pProgram->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    pProgram->link();
    pProgram->updateUniforms();

    pProgram->attachUniform("u_opacity");

    m_program=pProgram;
    m_program->retain();
    CHECK_GL_ERROR_DEBUG();
}
//-------------------------------------------------------------------------
bool FKCW_EffectNode_LightingBoltSprite::init()
{
    initProgram();

	this->CCSprite::initWithFile( "Engine/LightingBolt_lightingSeg.png" );
    this->setAnchorPoint(ccp(0,0));
    ccBlendFunc blendFuncSeg={GL_SRC_ALPHA,GL_ONE};
    this->setBlendFunc(blendFuncSeg);
	// �����
	this->getTexture()->setAntiAliasTexParameters();
	// ����mesh
	m_mesh=new FKCW_EffectNode_Mesh();
    m_mesh->autorelease();
    m_mesh->retain();
    // ��������VBO
    m_indexVBO=new FKCW_EffectNode_IndexVBO();
    m_indexVBO->autorelease();
    m_indexVBO->retain();
    CHECK_GL_ERROR_DEBUG();

    return true;
}
//-------------------------------------------------------------------------
void FKCW_EffectNode_LightingBoltSprite::updateNGeneration()
{
    float lightingLen=2*ccpDistance(m_startPoint, m_endPoint)*sqrtf(0.25+m_k_offset*m_k_offset);
    int count=0;
    while(lightingLen>m_mainSegLen)
	{
        lightingLen/=2;
        count++;
    }
    m_nGeneration=count;
}
//-------------------------------------------------------------------------
vector<FKCW_EffectNode_LightingSeg*> FKCW_EffectNode_LightingBoltSprite::genSegesFromBranchSeg(FKCW_EffectNode_LightingSeg*branchSeg,int nGeneration)
{
	// �����֧�Σ��õ����Ӷ��б�
    if(nGeneration<=0)
	{
        return vector<FKCW_EffectNode_LightingSeg*>();
        CCLOG("warning:nGeneration<=0!");
    }
    vector<FKCW_EffectNode_LightingSeg*> segList;
	// ����֧�� ��Ϊ��ʼ��
    segList.push_back(branchSeg);
	// ��ʼ�𲽷ָ�
    int branchStartGenerationID=branchSeg->branchStartGenerationID;
    for(int i=branchStartGenerationID+1;i<branchStartGenerationID+1+nGeneration;i++)
	{
        vector<FKCW_EffectNode_LightingSeg*> tSegList;
        // �ָ���б��е�ȫ���Ӷ�
        int nseg=(int)segList.size();
        for(int j=0;j<nseg;j++)
		{
            FKCW_EffectNode_LightingSeg*seg=segList[j];						// ��ǰ��
            vector<FKCW_EffectNode_LightingSeg*> subseges=splitSeg(seg,i);	// �ָ�Σ���ȡ�Ӷ�
			// ���Ӷμ�����б���
            int nSubSeg=(int)subseges.size();
            for(int k=0;k<nSubSeg;k++)
			{
                tSegList.push_back(subseges[k]);
            }
        }
        // ������б�
        for(int j=0;j<nseg;j++)
		{
            delete segList[j];
            segList[j]=NULL;
        }
        segList=tSegList;
    }
    return segList;
}
//-------------------------------------------------------------------------
void FKCW_EffectNode_LightingBoltSprite::genLighting()
{
    genSeges();
    genMesh();
}
//-------------------------------------------------------------------------
void FKCW_EffectNode_LightingBoltSprite::genSeges()
{
	// ������б�
    int nSeg=(int)m_segList.size();
    for(int i=0;i<nSeg;i++)
	{
        delete m_segList[i];
        m_segList[i]=NULL;
    }
    m_segList.clear();

	// ���m_nGeneration==0��˵��������ճ���̫��
    if(m_nGeneration==0)
	{
        FKCW_EffectNode_LightingSeg* branchSeg=new FKCW_EffectNode_LightingSeg(this->m_startPoint,this->m_endPoint);
        branchSeg->branchID=0;
        branchSeg->branchStartGenerationID=0;
        branchSeg->generationID=0;
        branchSeg->branchEndPoint=this->m_endPoint;
        m_segList.push_back(branchSeg);
        m_headSeg=branchSeg;
        m_tailSeg=branchSeg;
        return;
    }
    // ������ʼ��������
    FKCW_EffectNode_LightingSeg* branchSeg=new FKCW_EffectNode_LightingSeg(this->m_startPoint,this->m_endPoint);
    branchSeg->branchID=0;
    branchSeg->branchStartGenerationID=0;
    branchSeg->generationID=0;
    branchSeg->branchEndPoint=this->m_endPoint;
    // ͨ�������Σ������Ӷ��б�
    m_segList=genSegesFromBranchSeg(branchSeg, m_nGeneration);
    // �ҵ�ͷβ��
    m_headSeg=m_segList[0];
    m_tailSeg=m_segList[(int)m_segList.size()-1];
    assert(m_headSeg->branchID==0&&m_headSeg->father==NULL);
    assert(m_tailSeg->branchID==0&&(int)m_tailSeg->childList.size()==0);
}
//-------------------------------------------------------------------------
vector<FKCW_EffectNode_LightingSeg*> FKCW_EffectNode_LightingBoltSprite::splitSeg(FKCW_EffectNode_LightingSeg*seg,int generationID)
{
    //  *-------seg-------*
    //  *--seg0--*--seg1--*

    vector<FKCW_EffectNode_LightingSeg*> seges;
    float maxOffset=seg->getLen()*m_k_offset;
    float offset=FKCW_Base_Utils::RandomInRange(-maxOffset,maxOffset);
    CCPoint midPoint=seg->getMidPoint()+ccpMult(seg->getRightNormal(),offset);
    FKCW_EffectNode_LightingSeg* seg0=new FKCW_EffectNode_LightingSeg(seg->startPoint,midPoint);
    FKCW_EffectNode_LightingSeg* seg1=new FKCW_EffectNode_LightingSeg(midPoint,seg->endPoint);
    seg0->branchID=seg->branchID;// �Ӷεķ�֧ID�̳��ڸ���
    seg0->branchStartGenerationID=seg->branchStartGenerationID;
    seg0->branchEndPoint=seg->branchEndPoint;
    seg0->generationID=seg->generationID+1;
    seg1->branchID=seg->branchID;
    seg1->branchStartGenerationID=seg->branchStartGenerationID;
    seg1->branchEndPoint=seg->branchEndPoint;
    seg1->generationID=seg->generationID+1;
    // ����seg0,seg1������
    seg0->father=seg->father;
    seg0->addChildRef(seg1);
    seg1->father=seg0;
    seg1->childList=seg->childList;
	// ����Դ���ھӵ�������Ϣ
    if(seg->father)
	{
        seg->father->addChildRef(seg0);
        seg->father->removeChildRef(seg);
    }
    for(int i=0;i<(int)seg->childList.size();i++)
	{
        FKCW_EffectNode_LightingSeg* child=seg->childList[i];
        child->father=seg1;
    }

	// ����˳����� seg0, seg2(����иö�), seg1 �����б��С�ע���˳�򲻿ɸ��ģ���Ϊ�������Ա�֤segList[0]һ����ͷ�Σ�
	// ��segList[seglist.size()-1]һ����β��
    seges.push_back(seg0);
    // �����֧
    float p=FKCW_Base_Utils::Pow(0.6,generationID-1);
	float r=FKCW_Base_Utils::Random01();
    if(r<p)		// ���ָ������ɷ�֧
    {
        float randomSmallAngle=FKCW_Base_Utils::RandomInRange(-3,3);
        float lengthScale=0.6*FKCW_Base_Utils::Pow(1.2, seg->branchID);
        CCPoint splitEnd=ccpMult(FKCW_Base_Utils::RotateVector2(seg0->getVec(),randomSmallAngle), lengthScale)+midPoint;
        FKCW_EffectNode_LightingSeg* seg2=new FKCW_EffectNode_LightingSeg(midPoint,splitEnd);
        seg2->branchID=seg->branchID+1;// ��֧IDΪ����֧ID+1
        seg2->branchStartGenerationID=generationID;
        seg2->branchEndPoint=seg2->endPoint;
        seg2->generationID=seg->generationID+1;
        // ����seg2�����ӹ�ϵ
        seg2->father=seg0;
        seg0->addChildRef(seg2);
        // ���seg2
        seges.push_back(seg2);
    }
    // ���seg1
    seges.push_back(seg1);
    return seges;
}
//-------------------------------------------------------------------------
void FKCW_EffectNode_LightingBoltSprite::doJitter()
{
    // ���ɷ�֧�б�
    vector<FKCW_EffectNode_LightingSeg*> branchList;
    {
        FKCW_EffectNode_LightingSeg*seg=m_headSeg;
        while(1)
		{
			// �α��������ɶ�
            FKCW_EffectNode_LightingSeg*nextSeg=NULL;
            int nChild=(int)seg->childList.size();
            if(nChild>1)
			{	// �����˶�����֧��
                for(int i=0;i<nChild;i++)
				{
                    FKCW_EffectNode_LightingSeg*_seg=seg->childList[i];
                    if(_seg->branchID==1)
					{
						// �ö��Ƕ�����֧�ĸ���
                        branchList.push_back(_seg);
                    }
					else if(_seg->branchID==0)
					{
                        nextSeg=_seg;
                    }
                }
            }
			else if(nChild==1)
			{
                nextSeg=seg->childList[0];
            }
			// ������һ���Σ����������������ѭ��
            if(nextSeg)
			{
                seg=nextSeg;
            }
			else
			{
                break;
            }
        }
    }
    
	// ��־��֧�Ƿ���Ҫ���ؽ�
    {
        int nbranch=(int)branchList.size();
        for(int i=0;i<nbranch;i++)
		{
            FKCW_EffectNode_LightingSeg*branchSeg=branchList[i];
			float f = FKCW_Base_Utils::Random01();
            if( f < m_percentageOfJitterBranch )
			{
                branchSeg->needReGenerate=true;
            }
			else
			{
                branchSeg->needReGenerate=false;
            }
        }
     }

	// �������ӡ�
	// ��һ����֧����Ҫ�ؽ�����������ΪNULL
    vector<FKCW_EffectNode_LightingSeg*> seedList((int)branchList.size());
    {
        int nSeed=(int)seedList.size();
        for(int i=0;i<nSeed;i++)
		{
            if(branchList[i]->needReGenerate)
			{
                FKCW_EffectNode_LightingSeg*seed=new FKCW_EffectNode_LightingSeg();
                *seed=*branchList[i];
                seed->endPoint=seed->branchEndPoint;
                seed->generationID=branchList[i]->branchStartGenerationID;
                seed->childList.clear();
                seedList[i]=seed;
            }
			else
			{
                seedList[i]=NULL;
            }
        }
    }

	// ������Ҫ�ؽ��ķ�֧
    releaseNeedReGenBranch(branchList,m_segList);
    
	// ΪsecondaryBranchList��ÿ�������Ӷ�
    int nSeed=(int)seedList.size();
    for(int i=0;i<nSeed;i++)
	{
        FKCW_EffectNode_LightingSeg *seed=seedList[i];
        if(seed==NULL)
			continue;
        seed->endPoint=seed->startPoint+ccpMult(FKCW_Base_Utils::RotateVector2(seed->getVec(),FKCW_Base_Utils::RandomInRange(-3, 3)),0.7);
        // Ϊ�ӷ�֧�������Ӷ�
        int nGeneration_seed=m_nGeneration-seed->branchStartGenerationID;
        if(nGeneration_seed<=0)
			continue;
        vector<FKCW_EffectNode_LightingSeg*> tSegList=genSegesFromBranchSeg(seed, nGeneration_seed);
        assert(tSegList[0]->father);
        assert((int)tSegList[(int)tSegList.size()-1]->childList.size()==0);
        // ����Ӷε����б���
        int ntSeg=(int)tSegList.size();
        for(int j=0;j<ntSeg;j++)
		{
            m_segList.push_back(tSegList[j]);
        }
    }

    genMesh();
}
//-------------------------------------------------------------------------
void FKCW_EffectNode_LightingBoltSprite::releaseNeedReGenBranch(vector<FKCW_EffectNode_LightingSeg*>&branchList,vector<FKCW_EffectNode_LightingSeg*>&segList)
{
    int nbranch=(int)branchList.size();
    for(int i=0;i<nbranch;i++)
	{
        FKCW_EffectNode_LightingSeg*branchSeg=branchList[i];
        if(branchSeg->needReGenerate)
		{
			// ���丸������б���ɾ���������ü���
            branchSeg->father->removeChildRef(branchSeg);
            // �ͷ�������֧
            releaseNeedReGenBranch_inn(branchSeg,segList);
        }
    }
	// �Ƴ����б���ȫ����Ԫ��
    int nseg=(int)segList.size();
    for(int i=0;i<nseg;i++)
	{
        if(segList[i]->needReGenerate)
		{
            delete segList[i];
            segList[i]=NULL;
        }
    }
    
    vector<FKCW_EffectNode_LightingSeg*> tSegList;
    for(int i=0;i<nseg;i++)
	{
        if(segList[i]!=NULL)
		{
            tSegList.push_back(segList[i]);
        }
    }
    segList=tSegList;
}
//-------------------------------------------------------------------------
void FKCW_EffectNode_LightingBoltSprite::releaseNeedReGenBranch_inn(FKCW_EffectNode_LightingSeg*seg,vector<FKCW_EffectNode_LightingSeg*>&segList)
{
    if(seg==NULL)return;
    seg->needReGenerate=true;
    int nChild=(int)seg->childList.size();
    for(int i=0;i<nChild;i++)
	{
        FKCW_EffectNode_LightingSeg*_seg=seg->childList[i];
        releaseNeedReGenBranch_inn(_seg,segList);
    }
}
//-------------------------------------------------------------------------
void FKCW_EffectNode_LightingBoltSprite::genMesh()
{
    // ��������
    {
        m_mesh->vlist.clear();
        m_mesh->IDtriList.clear();
        m_mesh->texCoordList.clear();
        m_mesh->colorList.clear();
        int nSeg=(int)m_segList.size();
        for(int i=0;i<nSeg;i++)
		{
            FKCW_EffectNode_LightingSeg*seg=m_segList[i];
            // Ϊÿ���μ��������
            //      v0        v3
            //       * -------*
            //       |segW/2  |
            //   end <--------- start
            //       |        |
            //       *--------*
            //      v1        v2
            const CCPoint&start=seg->startPoint;
            const CCPoint&end=seg->endPoint;
            CCPoint rightNorm=seg->getRightNormal();
            float segW=12*FKCW_Base_Utils::Pow(0.3,seg->branchID);
            float opacity=1.0*FKCW_Base_Utils::Pow(0.4, seg->branchID);
            CCPoint p0=end+ccpMult(rightNorm, segW/2);
            CCPoint p1=end+ccpMult(rightNorm, -segW/2);
            CCPoint p2=start+ccpMult(rightNorm, -segW/2);
            CCPoint p3=start+ccpMult(rightNorm, segW/2);
            {
                CCPoint mid=seg->getMidPoint();
                p0=mid+ccpMult(p0-mid, 8);
                p1=mid+ccpMult(p1-mid, 8);
                p2=mid+ccpMult(p2-mid, 8);
                p3=mid+ccpMult(p3-mid, 8); 
            }
            CCPoint texCoord0=CCPoint(0,0);
            CCPoint texCoord1=CCPoint(0,1);
            CCPoint texCoord2=CCPoint(1,1);
            CCPoint texCoord3=CCPoint(1,0);
            m_mesh->vlist.push_back(Cv2(p0.x,p0.y));int vID0=(int)m_mesh->vlist.size()-1;
            m_mesh->vlist.push_back(Cv2(p1.x,p1.y));int vID1=(int)m_mesh->vlist.size()-1;
            m_mesh->vlist.push_back(Cv2(p2.x,p2.y));int vID2=(int)m_mesh->vlist.size()-1;
            m_mesh->vlist.push_back(Cv2(p3.x,p3.y));int vID3=(int)m_mesh->vlist.size()-1;
            m_mesh->texCoordList.push_back(Cv2(texCoord0.x,texCoord0.y));
            m_mesh->texCoordList.push_back(Cv2(texCoord1.x,texCoord1.y));
            m_mesh->texCoordList.push_back(Cv2(texCoord2.x,texCoord2.y));
            m_mesh->texCoordList.push_back(Cv2(texCoord3.x,texCoord3.y));
            
            m_mesh->colorList.push_back(Cv4(1,1,1,opacity));
            m_mesh->colorList.push_back(Cv4(1,1,1,opacity));
            m_mesh->colorList.push_back(Cv4(1,1,1,opacity));
            m_mesh->colorList.push_back(Cv4(1,1,1,opacity));
            
            CIDTriangle IDtri0(vID0,vID1,vID2);
            CIDTriangle IDtri1(vID0,vID2,vID3);
            m_mesh->IDtriList.push_back(IDtri0);
            m_mesh->IDtriList.push_back(IDtri1);
        }
    }
    // ��������Ϣ�ύ��IndexVBO��
    {
		m_indexVBO->SubmitPos(m_mesh->vlist,GL_STREAM_DRAW);
		m_indexVBO->SubmitTexCoord(m_mesh->texCoordList,GL_STREAM_DRAW);
		m_indexVBO->SubmitColor(m_mesh->colorList, GL_STATIC_DRAW);
		m_indexVBO->SubmitIndex(m_mesh->IDtriList,GL_STREAM_DRAW);
        CHECK_GL_ERROR_DEBUG();
    } 
}
//-------------------------------------------------------------------------
void FKCW_EffectNode_LightingBoltSprite::setStartAndEnd(CCPoint start,CCPoint end)
{
    m_startPoint_parentSpace=start;
    m_endPoint_parentSpace=end;
    m_startPoint= CCPointApplyAffineTransform(m_startPoint_parentSpace,this->parentToNodeTransform());
    m_endPoint=CCPointApplyAffineTransform(m_endPoint_parentSpace,this->parentToNodeTransform());

	// ��Ϊ��ʼ�����ֹ�㷢���˸��䣬����segList�е�ȫ����λ��
    if(m_headSeg&&m_tailSeg)
    {
        CCPoint vec_headStartToStart=m_startPoint-m_headSeg->startPoint;
        int nseg=(int)m_segList.size();
        for(int i=0;i<nseg;i++)
		{
            FKCW_EffectNode_LightingSeg*seg=m_segList[i];
            seg->startPoint=seg->startPoint+vec_headStartToStart;
            seg->endPoint=seg->endPoint+vec_headStartToStart;
            if(seg->branchID==1&&seg->father->branchID==0)
			{	// �ӷ�֧�ĸ���
                seg->branchEndPoint=seg->branchEndPoint+vec_headStartToStart;
            }
        }
        
        // ��תsegList�е�ȫ����
        CCPoint vec_headStartToTailEnd=m_tailSeg->endPoint-m_headSeg->startPoint;
        CCPoint vec_headStartToEnd=this->m_endPoint-m_headSeg->startPoint;
        CCPoint cosA_sinA=FKCW_Base_Utils::CalculateCosASinAOfVec1ToVec2(vec_headStartToTailEnd, vec_headStartToEnd);
        float cosA=cosA_sinA.x;
        float sinA=cosA_sinA.y;
        for(int i=0;i<nseg;i++)
		{
            FKCW_EffectNode_LightingSeg*seg=m_segList[i];
            seg->startPoint=m_headSeg->startPoint+FKCW_Base_Utils::RotateVector2(seg->startPoint-m_headSeg->startPoint, cosA,sinA);
            seg->endPoint=m_headSeg->startPoint+FKCW_Base_Utils::RotateVector2(seg->endPoint-m_headSeg->startPoint, cosA,sinA);
            if(seg->branchID==1&&seg->father->branchID==0)
			{	// �ӷ�֧�ĸ���
                seg->branchEndPoint=m_headSeg->startPoint+FKCW_Base_Utils::RotateVector2(seg->branchEndPoint-m_headSeg->startPoint, cosA, sinA);
            }
        }
		// ��תsegList���б��� headSeg->startPoint �õ���Ϊ����
        float dis_headStartToEnd=ccpDistance(m_headSeg->startPoint, this->m_endPoint);
        float dis_headStartToTailEnd=ccpDistance(m_headSeg->startPoint, m_tailSeg->endPoint);
        float scaleFactor=dis_headStartToTailEnd==0?1:dis_headStartToEnd/dis_headStartToTailEnd;
        for(int i=0;i<nseg;i++)
		{
            FKCW_EffectNode_LightingSeg*seg=m_segList[i];
            seg->startPoint=m_headSeg->startPoint+ccpMult(seg->startPoint-m_headSeg->startPoint, scaleFactor);
            seg->endPoint=m_headSeg->startPoint+ccpMult(seg->endPoint-m_headSeg->startPoint, scaleFactor);
            if(seg->branchID==1&&seg->father->branchID==0)
			{	// �ӷ�֧�ĸ���
                seg->branchEndPoint=m_headSeg->startPoint+ccpMult(seg->branchEndPoint-m_headSeg->startPoint, scaleFactor);
            }
        }
		// ��ΪsegList���б���䣬������Ҫ��������mesh����ɾ�����
        genMesh();
    }
    updateNGeneration(); 
}
//-------------------------------------------------------------------------
void FKCW_EffectNode_LightingBoltSprite::debugDraw_segWireFrame(float lineWidth)
{
    glLineWidth(lineWidth);
    // ����DEBUG������
    int nIDtri=(int)m_mesh->IDtriList.size();
    for(int i=0;i<nIDtri;i++)
	{
        CIDTriangle&IDtri=m_mesh->IDtriList[i];
        Cv2&p0=m_mesh->vlist[IDtri.getvIDByIndex(0)];
        Cv2&p1=m_mesh->vlist[IDtri.getvIDByIndex(1)];
        Cv2&p2=m_mesh->vlist[IDtri.getvIDByIndex(2)];
        CCPoint vertices[3]={ccp(p0.x(),p0.y()),ccp(p1.x(),p1.y()),ccp(p2.x(),p2.y())};
        ccDrawPoly(vertices, 3, true);
	}
}
//-------------------------------------------------------------------------
void FKCW_EffectNode_LightingBoltSprite::debugDraw_segLineAndDot(float lineWidth,float pointSize)
{
     // ���ƶ��б�
     glLineWidth(lineWidth);
     ccPointSize(pointSize);
     int nSeg=(int)m_segList.size();
     for(int i=0;i<nSeg;i++)
	 {
         FKCW_EffectNode_LightingSeg*seg=m_segList[i];
         ccDrawLine(seg->startPoint, seg->endPoint);
         ccDrawPoint(seg->startPoint);
         ccDrawPoint(seg->endPoint);
     }
}
//-------------------------------------------------------------------------
void FKCW_EffectNode_LightingBoltSprite::draw()
{
    // ��������
    ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );
    // ����shader
    assert(m_program);
    this->setShaderProgram(m_program);
    FKCW_EffectNode_GLProgramWithUnifos* program=(FKCW_EffectNode_GLProgramWithUnifos*)this->getShaderProgram();
    ccGLEnable(m_eGLServerState);
    program->use();
    program->setUniformsForBuiltins();
    // �����Զ���ֵ
    float alpha=(float)this->getOpacity()/255.0*m_opacityZoom;
    program->passUnifoValue1f("u_opacity", alpha);
    bool isAttribPositionOn=FKCW_EffectNode_IndexVBO::IsEnabledAttribArrayPosition();
    bool isAttribColorOn=FKCW_EffectNode_IndexVBO::IsEnabledAttribArrayColor();
    bool isAttribTexCoordOn=FKCW_EffectNode_IndexVBO::IsEnabledAttribArrayTexCoord();
	FKCW_EffectNode_IndexVBO::EnableAttribArrayPosition(true);
	FKCW_EffectNode_IndexVBO::EnableAttribArrayTexCoord(true);
	FKCW_EffectNode_IndexVBO::EnableAttribArrayColor(true);
    // �����
    ccGLBindTexture2D( this->getTexture()->getName());
    // ʵ�ʻ���
	m_indexVBO->SetPointerPosition();
	m_indexVBO->SetPointerTexCoord();
	m_indexVBO->SetPointerColor();
    m_indexVBO->Draw(GL_TRIANGLES);
	FKCW_EffectNode_IndexVBO::EnableAttribArrayPosition(isAttribPositionOn);
	FKCW_EffectNode_IndexVBO::EnableAttribArrayColor(isAttribColorOn);
	FKCW_EffectNode_IndexVBO::EnableAttribArrayTexCoord(isAttribTexCoordOn);
    // ��������
    ccGLBindTexture2D(0);
   
    // DEBUG����
    if(m_isDrawDebug)
	{
        debugDraw_segLineAndDot(0.5,3);
    }
    CHECK_GL_ERROR_DEBUG();
}
//---------------------------------------------
bool FKCW_EffectNode_LightingBoltNode::init(const CCPoint&start,const CCPoint&end)
{
    m_start=start;
    m_end=end;
    //lightingSprit
    {
        m_lbSprite=new FKCW_EffectNode_LightingBoltSprite();
        m_lbSprite->autorelease();
        m_lbSprite->init();
        m_lbSprite->setStartAndEnd(m_start, m_end);
        m_lbSprite->genLighting();
        this->addChild(m_lbSprite);
    }
    //lightingSprit2
    {
        m_lbSprite2=new FKCW_EffectNode_LightingBoltSprite();
        m_lbSprite2->autorelease();
        m_lbSprite2->init();
        m_lbSprite2->setStartAndEnd(m_start, m_end);
        m_lbSprite2->genLighting();
        this->addChild(m_lbSprite2);
    }
    return true;
}
//-------------------------------------------------------
// CflashAction
//-------------------------------------------------------
FKCW_Action_FlashAction::FKCW_Action_FlashAction()
{
	_InitMembers();
}
//-------------------------------------------------------
FKCW_Action_FlashAction::~FKCW_Action_FlashAction()
{
}
//-------------------------------------------------------
void FKCW_Action_FlashAction::_InitMembers()
{
	m_timeFoe=0;
	m_timeCur=0;
	m_oneFlashTime=0;
	m_jitterTimeOfOneFlash=0;
	m_jitterInterval=0;
	m_isDoJitter=true;
	m_startOpacity=255;
	m_endOpacity=80;
}
//-------------------------------------------------------
FKCW_Action_FlashAction* FKCW_Action_FlashAction::create(float fDuration,float oneFlashTime){
    
    FKCW_Action_FlashAction *p = new FKCW_Action_FlashAction();
    p->initWithDuration(fDuration, oneFlashTime);
    p->autorelease();
    
    return p;
}
//-------------------------------------------------------
bool FKCW_Action_FlashAction::initWithDuration(float fDuration,float oneFlashTime){
    if (CCActionInterval::initWithDuration(fDuration))
    {
		_InitMembers();
        m_oneFlashTime=oneFlashTime;
        return true;
    }
    return false;
}
//-------------------------------------------------------
bool FKCW_Action_FlashAction::isDone()
{
    if(getDuration()==-1)
	{
        return false;
    }
	else
	{
        return CCActionInterval::isDone();
    }
}
//-------------------------------------------------------
void FKCW_Action_FlashAction::stop()
{
    _StopAnimation(m_pTarget);
    CCActionInterval::stop();
}
//-------------------------------------------------------
void FKCW_Action_FlashAction::startWithTarget(CCNode *pTarget)
{
    _StartAnimation(pTarget);
    CCActionInterval::startWithTarget(pTarget);  
}
//-------------------------------------------------------
void FKCW_Action_FlashAction::update(float time)
{
/*  if(false)
	{
        m_timeFoe=m_timeCur;
        float progressPercentage=time;
        m_timeCur=progressPercentage*getDuration();
        ((ClightningBoltNode*)m_pTarget)->updateFlashAction(m_timeCur,m_timeCur-m_timeFoe);
    }
*/    
}
//-------------------------------------------------------
void FKCW_Action_FlashAction::_StartAnimation(CCNode*pTarget)
{
    FKCW_EffectNode_LightingBoltNode*	lbNode=(FKCW_EffectNode_LightingBoltNode*)pTarget;
    FKCW_EffectNode_LightingBoltSprite*	lbSprite=lbNode->m_lbSprite;
    FKCW_EffectNode_LightingBoltSprite*	lbSprite2=lbNode->m_lbSprite2;
 
    _StopAnimation(pTarget);

    lbSprite->setOpacity(m_startOpacity);
    lbSprite2->setOpacity(m_endOpacity);
    // ִ�ж���
    CCDelayTime*delay=CCDelayTime::create(m_oneFlashTime/2);
    CCCallFuncN*callFunc_flashForever=CCCallFuncN::create(this,callfuncN_selector(FKCW_Action_FlashAction::_CallBack_flashForever));
    CCAction*action=CCSequence::create(callFunc_flashForever,NULL);
    CCAction*action2=CCSequence::create(delay,callFunc_flashForever,NULL);
    lbSprite->runAction(action);
    lbSprite2->runAction(action2);
}
//-------------------------------------------------------
void FKCW_Action_FlashAction::_StopAnimation(CCNode*pTarget)
{
    FKCW_EffectNode_LightingBoltNode*	lbNode=(FKCW_EffectNode_LightingBoltNode*)pTarget;
    FKCW_EffectNode_LightingBoltSprite*	lbSprite=lbNode->m_lbSprite;
    FKCW_EffectNode_LightingBoltSprite*	lbSprite2=lbNode->m_lbSprite2;
    lbSprite->stopAllActions();
    lbSprite2->stopAllActions();
}
//-------------------------------------------------------
void FKCW_Action_FlashAction::_CallBack_flashForever(CCNode*sender)
{
    m_jitterTimeOfOneFlash	=m_oneFlashTime/4;
    m_jitterInterval		=m_oneFlashTime/6;
	// ��������
    CCFadeTo*		fadeTo=CCFadeTo::create(m_oneFlashTime, m_endOpacity) ;
	CCCallFuncN*	callFunc_genLightning=CCCallFuncN::create(this,callfuncN_selector(FKCW_Action_FlashAction::_CallBack_genLightning));
	CCCallFuncN*	callFunc_jitter=CCCallFuncN::create(this,callfuncN_selector(FKCW_Action_FlashAction::_CallBack_jitter));
	CCCallFuncN*	callFunc_resetOpacity=CCCallFuncN::create(this, callfuncN_selector(FKCW_Action_FlashAction::_CallBack_resetOpacity));
    // ��������
    CCDelayTime*	delay_jitterInterval=CCDelayTime::create(m_jitterInterval);
    CCArray*		array=CCArray::create();
    float totalTime=0;
    while(true) 
	{
        if(totalTime>=m_jitterTimeOfOneFlash)break;
        array->addObject(delay_jitterInterval);
        if(m_isDoJitter)array->addObject(callFunc_jitter);
        totalTime+=m_jitterInterval;
    }
    CCSequence*seq=CCSequence::create(array);
    CCAction*action=CCRepeatForever::create(CCSpawn::create(seq,CCSequence::create(callFunc_resetOpacity,fadeTo,callFunc_genLightning,NULL),NULL));
    // ִ����������
    ((FKCW_EffectNode_LightingBoltSprite*)sender)->runAction(action); 
}
//-------------------------------------------------------
void FKCW_Action_FlashAction::_CallBack_genLightning(CCNode* sender)
{
    ((FKCW_EffectNode_LightingBoltSprite*)sender)->genLighting();
}
//-------------------------------------------------------
void FKCW_Action_FlashAction::_CallBack_jitter(CCNode*sender)
{
    ((FKCW_EffectNode_LightingBoltSprite*)sender)->doJitter();
}
//-------------------------------------------------------
void FKCW_Action_FlashAction::_CallBack_resetOpacity(CCNode*sender)
{
    ((FKCW_EffectNode_LightingBoltSprite*)sender)->setOpacity(m_startOpacity);
}
//-------------------------------------------------------