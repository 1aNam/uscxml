#include "V8NodeSet.h"
#include "V8Element.h"
#include "V8Node.h"

namespace Arabica {
namespace DOM {

v8::Handle<v8::Value> V8NodeSet::indexedPropertyCustomGetter(uint32_t index, const v8::AccessorInfo &info) {
	v8::Local<v8::Object> self = info.Holder();
	V8NodeSetPrivate* privData = V8DOM::toClassPtr<V8NodeSetPrivate >(self->GetInternalField(0));

	if (privData->arabicaThis->size() >= index) {
		switch((*privData->arabicaThis)[index].getNodeType()) {
		case Node_base::ELEMENT_NODE: {
			Arabica::DOM::Element<std::string>* retVal = new Arabica::DOM::Element<std::string>((*privData->arabicaThis)[index]);

			v8::Handle<v8::Function> retCtor = V8Element::getTmpl()->GetFunction();
			v8::Persistent<v8::Object> retObj = v8::Persistent<v8::Object>::New(retCtor->NewInstance());

			struct V8Element::V8ElementPrivate* retPrivData = new V8Element::V8ElementPrivate();
			retPrivData->dom = privData->dom;
			retPrivData->arabicaThis = retVal;

			retObj->SetInternalField(0, V8DOM::toExternal(retPrivData));

			retObj.MakeWeak(0, V8Element::jsDestructor);
			return retObj;
		}
		default: {
			Arabica::DOM::Node<std::string>* retVal = new Arabica::DOM::Node<std::string>((*privData->arabicaThis)[index]);

			v8::Handle<v8::Function> retCtor = V8Node::getTmpl()->GetFunction();
			v8::Persistent<v8::Object> retObj = v8::Persistent<v8::Object>::New(retCtor->NewInstance());

			struct V8Node::V8NodePrivate* retPrivData = new V8Node::V8NodePrivate();
			retPrivData->dom = privData->dom;
			retPrivData->arabicaThis = retVal;

			retObj->SetInternalField(0, V8DOM::toExternal(retPrivData));

			retObj.MakeWeak(0, V8Node::jsDestructor);
			return retObj;
		}
		}
	}

	return v8::Undefined();

}

}
}