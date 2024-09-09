#include "ccpch.h"
#include "LayerStack.h"

//namespace Cannis {
//	LayerStack::LayerStack() {
//		m_layerInsert = m_layers.begin();
//	}
//
//	LayerStack::~LayerStack() {
//		for (Layer* layer : m_layers)
//			delete layer;
//	}
//
//	void LayerStack::PushLayer(Layer* p_layer) {
//		m_layerInsert = m_layers.emplace(m_layerInsert, p_layer);
//	}
//
//	void LayerStack::PushOverlay(Layer* p_overlay) {
//		
//	}
//
//	void LayerStack::PopLayer(Layer* p_layer) {
//		auto it = std::find(m_layers.begin(), m_layers.end(), p_layer);
//		if (it != m_layers.end()) {
//			m_layers.erase(it);
//			m_layerInsert--;
//		}
//	}
//	void LayerStack::PopOverlay(Layer* p_overlay) {
//		auto it = std::find(m_layers.begin(), m_layers.end(), p_overlay);
//		if (it != m_layers.end()) {
//			m_layers.erase(it);
//		}
//	}
//}