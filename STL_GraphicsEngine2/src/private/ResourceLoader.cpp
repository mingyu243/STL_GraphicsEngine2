#include "ResourceLoader.h"

#include <wrl.h>
using Microsoft::WRL::ComPtr;

ID3D11ShaderResourceView* ResourceLoader::LoadTextureFromFile(ID3D11Device* device, std::wstring filename)
{
	filename = std::wstring(L"..//res//textures//") + filename;

	// 스크래치 이미지 생성.
	DirectX::ScratchImage image;
	HRESULT result = GetScratchImage(filename, &image);

	// 오류 검사.
	if (FAILED(result))
	{
		MessageBox(nullptr, L"스크래치 이미지 로드 실패", L"오류", 0);
		//throw std::exception("스크래치 이미지 로드 실패");
		return nullptr;
	}

	// 텍스쳐 생성.
	ComPtr<ID3D11Texture2D> texture;
	result = DirectX::CreateTexture(
		device,
		image.GetImages(),
		image.GetImageCount(),
		image.GetMetadata(),
		(ID3D11Resource**)texture.GetAddressOf()
	);

	// 오류 검사.
	if (FAILED(result))
	{
		MessageBox(nullptr, L"텍스처 생성 실패", L"오류", 0);
		//throw std::exception("텍스처 생성 실패");
		return nullptr;
	}

	// 쉐이더 리소스 뷰 생성.
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));

	srvDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	D3D11_TEXTURE2D_DESC textureDesc;
	texture->GetDesc(&textureDesc);

	srvDesc.Format = textureDesc.Format;

	ID3D11ShaderResourceView* shaderResourceView;
	result = device->CreateShaderResourceView(
		texture.Get(),
		&srvDesc,
		&shaderResourceView
	);

	// 오류 검사.
	if (FAILED(result))
	{
		MessageBox(nullptr, L"셰이더 리소스 뷰 생성 실패", L"오류", 0);
		//throw std::exception("셰이더 리소스 뷰 생성 실패");
		return nullptr;
	}

	return shaderResourceView;
}

void ResourceLoader::LoadModel(std::string filename, std::vector<Vertex>* vertices)
{
	// 리소스 경로 추가.
	filename = std::string("..//res//models//") + filename;

	// 옵션 설정.
	const aiScene* scene = aiImportFile(
		filename.c_str(),
		aiProcess_JoinIdenticalVertices |
		aiProcess_ValidateDataStructure |
		aiProcess_ImproveCacheLocality |
		aiProcess_RemoveRedundantMaterials |
		aiProcess_GenUVCoords |
		aiProcess_TransformUVCoords |
		aiProcess_FindInstances |
		aiProcess_LimitBoneWeights |
		aiProcess_OptimizeMeshes |
		aiProcess_GenSmoothNormals |
		aiProcess_SplitLargeMeshes |
		aiProcess_Triangulate | // 폴리곤이 사각형이면, 삼각형을 쪼갬. 엔진에서도 다 그럼.
		aiProcess_ConvertToLeftHanded |
		aiProcess_SortByPType
	);

	// 임포트.
	if (scene != nullptr)
	{
		const aiMesh* mesh = scene->mMeshes[0]; // 원래는 여러 개 있을 수도 있어서, 루프 돌아야 함.
		vertices->reserve(mesh->mNumVertices);

		// 정점 배열 채우기.
		for (int ix = 0; ix < mesh->mNumVertices; ix++)
		{
			// 위치 읽어오기
			Vector3f position = Vector3f(
				mesh->mVertices[ix].x,
				mesh->mVertices[ix].y,
				mesh->mVertices[ix].z
			);

			Vertex vertex = Vertex(position.x, position.y, position.z);
			vertices->push_back(vertex);
		}
	}
	else
	{
		MessageBox(nullptr, L"모델 로드 실패", L"오류", 0);
		throw std::exception("모델 로드 실패");
	}
}

void ResourceLoader::LoadModel(std::string filename, std::vector<VertexUV>* vertices)
{
	// 리소스 경로 추가.
	filename = std::string("..//res//models//") + filename;

	// 옵션 설정.
	const aiScene* scene = aiImportFile(
		filename.c_str(),
		aiProcess_JoinIdenticalVertices |
		aiProcess_ValidateDataStructure |
		aiProcess_ImproveCacheLocality |
		aiProcess_RemoveRedundantMaterials |
		aiProcess_GenUVCoords |
		aiProcess_TransformUVCoords |
		aiProcess_FindInstances |
		aiProcess_LimitBoneWeights |
		aiProcess_OptimizeMeshes |
		aiProcess_GenSmoothNormals |
		aiProcess_SplitLargeMeshes |
		aiProcess_Triangulate | // 폴리곤이 사각형이면, 삼각형을 쪼갬. 엔진에서도 다 그럼.
		aiProcess_ConvertToLeftHanded |
		aiProcess_SortByPType
	);

	// 임포트.
	if (scene != nullptr)
	{
		const aiMesh* mesh = scene->mMeshes[0]; // 원래는 여러 개 있을 수도 있어서, 루프 돌아야 함.
		vertices->reserve(mesh->mNumVertices);

		// 정점 배열 채우기.
		for (int ix = 0; ix < mesh->mNumVertices; ix++)
		{
			// 위치 읽어오기.
			Vector3f position = Vector3f(
				mesh->mVertices[ix].x,
				mesh->mVertices[ix].y,
				mesh->mVertices[ix].z
			);

			// UV 읽어오기.
			Vector2f uv;
			if (mesh->HasTextureCoords(0))
			{
				uv = Vector2f(
					mesh->mTextureCoords[0][ix].x,
					mesh->mTextureCoords[0][ix].y
				);
			}
			else
			{
				uv = Vector2f(0.0f, 0.0f);
			}

			VertexUV vertex = VertexUV(position, uv);
			vertices->push_back(vertex);
		}
	}
	else
	{
		MessageBox(nullptr, L"모델 로드 실패", L"오류", 0);
		throw std::exception("모델 로드 실패");
	}
}

std::wstring ResourceLoader::GetExtension(std::wstring str)
{
	size_t size = str.rfind('.', str.length());
	if (size != std::wstring::npos)
	{
		return (str.substr(size + 1, str.length() - size));
	}
	return std::wstring();
}

HRESULT ResourceLoader::GetScratchImage(std::wstring filename, DirectX::ScratchImage* image)
{
	// 파일의 확장자 구하기 (ex: jpg/png/tga).
	std::wstring extension = GetExtension(filename);

	if (extension._Equal(L"tga") || extension._Equal(L"TGA"))
	{
		return DirectX::LoadFromTGAFile(filename.c_str(), NULL, *image);
	}
	else if (extension._Equal(L"dds") || extension._Equal(L"DDS"))
	{
		return DirectX::LoadFromDDSFile(filename.c_str(), DirectX::DDS_FLAGS_NONE, NULL, *image);
	}
	else // 다른 확장자 파일들.
	{
		return DirectX::LoadFromWICFile(filename.c_str(), DirectX::WIC_FLAGS_NONE, NULL, *image);
	}

	return E_NOTIMPL;
}
