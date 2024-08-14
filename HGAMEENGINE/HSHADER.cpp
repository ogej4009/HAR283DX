#include "HSHADER.h"
#include <HGAMEFILE.h>
#include "HVTXSHADER.h"
#include "HPIXSHADER.h"
#include "HGEOMETRYSHADER.h"

void HSHADER::AutoShaderCompile(const HGAMESTRING& _FilePath)
{
	if (std::wstring::npos != _FilePath.Find("Particle.hlsl"))
	{
		int a = 0;
	}

	HGAMEFILE File = HGAMEFILE(_FilePath, L"rt");
	HGAMESTRING AllText = File.AllText();

	std::list<HSTRINGDATA> AllData = AllText.AllFindData(L"(");

	std::list<HSTRINGDATA> Name;
	std::list<HSTRINGDATA> Para;

	std::list<HSTRINGDATA>::iterator Start = AllData.begin();
	std::list<HSTRINGDATA>::iterator End = AllData.end();

	// fasdfasdfas (

	for (; Start != End; ++Start)
	{
		Name.push_back(AllText.RerversTrimToTrim((*Start).StartPos - 1));
		Para.push_back(AllText.TrimToTrim((*Start).EndPos));
	}

	int a = 0;

	{
		std::list<HSTRINGDATA>::iterator NameStart = Name.begin();
		std::list<HSTRINGDATA>::iterator NameEnd = Name.end();

		std::list<HSTRINGDATA>::iterator ParaStart = Para.begin();
		std::list<HSTRINGDATA>::iterator ParaEnd = Para.end();

		std::list<HSTRINGDATA> AllFunc = std::list<HSTRINGDATA>();

		for (; NameStart != NameEnd;)
		{
			if (std::wstring::npos != NameStart->Text.Find(L"GS_Particle"))
			{
				int a = 0;
			}

			if (L"register" == (*NameStart).Text || L"" == (*NameStart).Text)
			{
				NameStart = Name.erase(NameStart);
				ParaStart = Para.erase(ParaStart);
			}
			else if (L"point" == (*ParaStart).Text)
			{
				++NameStart;
				++ParaStart;
				// 지오메트리 쉐이더.
			}
			else 
			{
				std::list<HSTRINGDATA> FindParaList = AllText.RerversAllFindData((*ParaStart).Text, (*ParaStart).StartPos);

				if (0 == FindParaList.size())
				{
					NameStart = Name.erase(NameStart);
					ParaStart = Para.erase(ParaStart);
				}
				else if (0 != FindParaList.size())
				{
					HSTRINGDATA Data;
					for (auto& _ShaderFind : FindParaList)
					{
						Data = AllText.RerversTrimToTrim(_ShaderFind.StartPos - 1);
						if (L"struct" == Data.Text)
						{
							break;
						}
					}

					if (L"struct" == Data.Text)
					{
						++NameStart;
						++ParaStart;
					}
					else {
						NameStart = Name.erase(NameStart);
						ParaStart = Para.erase(ParaStart);
					}

				}
				else {
					++NameStart;
					++ParaStart;
				}
				int a = 0;
			}
		}
	}

	if (true == Name.empty())
	{
		AMSG(L"함수가 하나도 들어있지 않습니다.");
		return;
	}

	if (Name.size() != Para.size())
	{
		AMSG(L"함수와 파라미터의 개수가 다릅니다.");
		return;
	}

	a = 0;
	{
		std::list<HSTRINGDATA>::iterator NameStart = Name.begin();
		std::list<HSTRINGDATA>::iterator NameEnd = Name.end();

		std::list<HSTRINGDATA>::iterator ParaStart = Para.begin();
		std::list<HSTRINGDATA>::iterator ParaEnd = Para.end();

		// 이녀석은 결정 되어야 한다.
		// 버텍스 쉐이더 인지픽셀쉐이더 인지 결정되어야 한다.
		for (; NameStart != NameEnd;++NameStart)
		{
			if (NameStart->Text == "VS_Particle")
			{
				int a = 0;
			}

			if (NameStart->Text == "PS_Particle")
			{
				int a = 0;
			}



			// 여기서 반대쪽에 있는 공백과 공백사이에 있는 녀석은
			// 함수의 리턴 값이다.
			HSTRINGDATA ReturnData = AllText.RerversTrimToTrim(NameStart->StartPos - 1);

			// 지오메트리 쉐이더.
			if (L"void" == ReturnData.Text) 
			{
				HGEOMETRYSHADER::Load(_FilePath, NameStart->Text);
			}

			if (L"float4" == ReturnData.Text)
			{
				size_t FindStartPos = AllText.Find(L")", ReturnData.EndPos);
				FindStartPos = AllText.Find(L":", FindStartPos);

				HSTRINGDATA SementicData = AllText.TrimToTrim(FindStartPos + 1);

				if (0 == SementicData.Text.Find(L"SV_Position"))
				{
					HVTXSHADER::Load(_FilePath, NameStart->Text);
				}
				else if (0 == SementicData.Text.Find(L"SV_Target"))
				{
					HPIXSHADER::Load(_FilePath, NameStart->Text);
				}
				else 
				{
					AMSG(L"쉐이더 타입을 구분할 수 없는 상황입니다");
				}
			}
			else 
			{

				std::list<HSTRINGDATA> FindReturnList = AllText.RerversAllFindData(ReturnData.Text, ReturnData.StartPos);

				if (0 == FindReturnList.size())
				{
					AMSG(L"함수에 리턴값이 존재하지 않습니다. \n 참조파일까지 모두 찾아봐야하는 상황입니다. 혹은 함수이름 분석 오류입니다.");
				}
				else if (0 != FindReturnList.size())
				{
					HSTRINGDATA FindData;
					bool Check = false;

					for (auto& _Shader : FindReturnList)
					{
						FindData = AllText.RerversTrimToTrim(_Shader.StartPos - 1);

						if (L"struct" == FindData.Text)
						{
							size_t LastPos = AllText.Find(L"}", FindData.EndPos);
							HGAMESTRING StructText = AllText.Cut(FindData.EndPos + 1, LastPos);

							if (std::wstring::npos != StructText.Find(L"SV_Position"))
							{
								HVTXSHADER::Load(_FilePath, NameStart->Text);
								Check = true;
							}
							else if (std::wstring::npos != StructText.Find(L"FOG"))
							{
								HVTXSHADER::Load(_FilePath, NameStart->Text);
								Check = true;
							}
							else if (std::wstring::npos != StructText.Find(L"SV_Target"))
							{
								HPTR<HPIXSHADER> PTR = HPIXSHADER::Load(_FilePath, NameStart->Text);

								HGAMESTRING Text = StructText.ToUpperReturn();

								if (std::wstring::npos != Text.Find(L"DEFFERD"))
								{
									PTR->RPType(RENDERPATHTYPE::RP_DEFFERD);
									int a = 0;
								}

								if (std::wstring::npos != Text.Find(L"FORWARD"))
								{
									PTR->RPType(RENDERPATHTYPE::RP_FORWARD);
									int a = 0;
								}

								Check = true;
							}
							else 
							{
								AMSG(L"쉐이더 타입을 구분할 수 없는 상황입니다");
							}
						}
						else {
							AMSG(L"쉐이더 타입을 구분할 수 없는 상황입니다");
						}
					}
					if (Check == false)
					{
						AMSG(L"쉐이더 타입을 구분할 수 없는 상황입니다");
					}
				}
			}
		}
	}
}

void HSHADER::ResCheck() 
{
	ID3D11ShaderReflection* Reflector = nullptr;

	if (S_OK
		!=
		D3DReflect(m_pBlob->GetBufferPointer(), m_pBlob->GetBufferSize()
			, IID_ID3D11ShaderReflection, (void**)&Reflector))
	{
	}

	D3D11_SHADER_DESC ShaderDesc;
	Reflector->GetDesc(&ShaderDesc);

	// 모든 리소스 개수 알아오기
	D3D11_SHADER_INPUT_BIND_DESC ResDesc;
	SHADERDATA SData;
	for (unsigned int i = 0; i < ShaderDesc.BoundResources; i++)
	{
		Reflector->GetResourceBindingDesc(i, &ResDesc);

		SData.Name = ResDesc.Name;
		SData.m_ShaderType = m_Type;
		SData.m_Index = ResDesc.BindPoint;
		SData.m_DataType = ResDesc.Type;
		
		switch (ResDesc.Type)
		{
		case D3D_SIT_CBUFFER:
		{
			ID3D11ShaderReflectionConstantBuffer* ConstBufferData = Reflector->GetConstantBufferByName(ResDesc.Name);
			D3D11_SHADER_BUFFER_DESC BufferDesc;
			ConstBufferData->GetDesc(&BufferDesc);
			SData.m_Size = BufferDesc.Size;
			break;
		}
		case D3D_SIT_TEXTURE:
			break;
		case D3D_SIT_SAMPLER:
			break;
		case D3D_SIT_STRUCTURED:
			// 지오메트리 쉐이더용 

			ppDesc = &m_StructuredBufferName2Descriptor.Add(BindDesc.Name);
			pShaderParameter->mpBufferParameterName[bufferIndex] = s2ws(desc.Name);
			pShaderParameter->mpBufferParameterBindPoint[bufferIndex] = desc.BindPoint;
			bufferIndex++;

			HRESULT hr = Reflector->GetResourceBindingDescByName(ResDesc.Name, &ResDesc);
			break;
		default:
			AMSG(L"아직 처리하는 방식을 정하지 않은 리소스 입니다.");
			break;
		}

		if (m_ResData.end() != m_ResData.find(ResDesc.Name))
		{
			AMSG(L"중복 리소스가 존재합니다.");
		}

		m_ResData[ResDesc.Name] = SData;
	}

}