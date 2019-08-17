#include "pch.h"
#include "TextureLayer.h"

namespace Demo
{
	TextureLayer::TextureLayer()
		: Layer(TO_STRING(TextureLayer))
	{
		vertexArray = new VertexArray();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f, 0.0f, 1.0f
		};
		VertexBuffer* vertexBuffer = new VertexBuffer(vertices, sizeof(vertices));
		vertexBuffer->SetLayout({
			{ GLSLDataType::Vec3, "in_position" },
			{ GLSLDataType::Vec4, "in_color" },
			{ GLSLDataType::Vec2, "in_textureCoordinate"}
		});
		vertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[] = { 
			0, 1, 2,
			2, 3, 0
		};
		IndexBuffer* indexBuffer = new IndexBuffer(indices, sizeof(indices));
		vertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 in_position;
			layout(location = 1) in vec4 in_color;
			layout(location = 2) in vec2 in_textureCoordinate;

			out Vertex {
				vec4 color;
				vec2 textureCoordinate;
			} out_vertex;

			void main()
			{
				out_vertex.color = in_color;
				out_vertex.textureCoordinate = in_textureCoordinate;
				gl_Position = vec4(in_position, 1.0);
			}
		)";
		std::string fragmentSource = R"(
			#version 330 core

			in Vertex {
				vec4 color;
				vec2 textureCoordinate;
			} in_vertex;

			uniform sampler2D sampler;

			out vec4 out_color;
			
			void main()
			{
				out_color = texture(sampler, in_vertex.textureCoordinate);
			}
		)";
		shader = new Shader(vertexSource, fragmentSource);

		texture = new Texture("assets/kitten.png");
	}

	TextureLayer::~TextureLayer()
	{
		delete texture;
		delete shader;
		delete vertexArray;
	}

	void TextureLayer::OnAttach()
	{
		texture->Bind();
		shader->Bind();
		vertexArray->Bind();
	}

	void TextureLayer::OnDetach()
	{
		texture->Unbind();
		shader->Unbind();
		vertexArray->Unbind();
	}

	void TextureLayer::OnUpdate()
	{
	}

	void TextureLayer::OnRender(Renderer* renderer)
	{
		renderer->DrawElements(vertexArray->GetIndexBuffer());
	}

	void TextureLayer::OnImGuiRender()
	{
	}

	void TextureLayer::OnEvent(const Event& event)
	{
	}
}