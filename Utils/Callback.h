#pragma once

#include "Sugar.h"

namespace Utils {
	// ------------------------------------------------------------------------
	// Callback interface
	
	template<typename _ArgType = void, typename _RetType = void>
	class ICallback {
	public:
		ICallback() {}
		virtual ~ICallback() {}

		_RetType operator()(_ArgType arg) {
			return this->call(arg);
		}

		virtual bool		isValid	() const = 0;
		virtual _RetType	call	(_ArgType) = 0;
	};

	template<typename _ArgType>
	class ICallback<_ArgType, void> {
	public:
		ICallback() {}
		virtual ~ICallback() {}

		void operator()(_ArgType arg) {
			this->call(arg);
		}

		virtual bool isValid() const = 0;
		virtual void call(_ArgType) = 0;
	};

	template<>
	class ICallback<void, void> {
	public:
		ICallback() {}
		virtual ~ICallback() {}

		void operator()() {
			this->call();
		}

		virtual bool isValid() const = 0;
		virtual void call() = 0;
	};
	
	// ------------------------------------------------------------------------
	// Callback-function

	template<typename _ArgType = void, typename _RetType = void>
	class FcnCallback : public ICallback<_ArgType, _RetType> {
	public:
		FcnCallback(_RetType(*_callback)(_ArgType) = nullptr) :
			ICallback<_ArgType, _RetType>(), callback(nullptr) {
			this->set(_callback);
		}
		virtual ~FcnCallback() {}

		virtual bool isValid() const override {
			return (this->callback != nullptr);
		}

		void set(_RetType(*_callback)(_ArgType)) {
			this->callback = _callback;
		}

		virtual _RetType call(_ArgType arg) override {
			return this->callback(arg);
		}
	private:
		_RetType(*callback)(_ArgType);
	};

	template<typename _ArgType>
	class FcnCallback<_ArgType, void> : public ICallback<_ArgType, void> {
	public:
		FcnCallback(void(*_callback)(_ArgType) = nullptr) :
			ICallback<_ArgType, void>(), callback(nullptr) {
			this->set(_callback);
		}
		virtual ~FcnCallback() {}

		virtual bool isValid() const override {
			return (this->callback != nullptr);
		}

		void set(void(*_callback)(_ArgType)) {
			this->callback = _callback;
		}

		virtual void call(_ArgType arg) override {
			this->callback(arg);
		}
	private:
		void(*callback)(_ArgType);
	};

	template<>
	class FcnCallback<void, void> : public ICallback<void, void> {
	public:
		FcnCallback(void(*_callback)() = nullptr) :
			ICallback<void, void>(), callback(nullptr) {
			this->set(_callback);
		}
		virtual ~FcnCallback() {}

		virtual bool isValid() const override {
			return (this->callback != nullptr);
		}

		void set(void(*_callback)()) {
			this->callback = _callback;
		}

		virtual void call() override {
			this->callback();
		}
	private:
		void(*callback)();
	};

	// ------------------------------------------------------------------------
	// Callback-method

	template<typename _ObjType, typename _ArgType = void, typename _RetType = void>
	class ObjCallback : public ICallback<_ArgType, _RetType> {
	public:
		ObjCallback(_ObjType* _obj = nullptr, _RetType(_ObjType::*_method)(_ArgType) = nullptr) :
			ICallback<_ArgType, _RetType>(), obj(nullptr), method(nullptr) {
			this->set(_obj, _method);
		}
		virtual ~ObjCallback() {}

		virtual bool isValid() const override {
			return ( (this->method != nullptr) && (this->obj != nullptr) );
		}

		void set(_ObjType* _obj, _RetType(_ObjType::*_method)(_ArgType)) {
			this->obj = _obj;
			this->method = _method;
		}

		virtual _RetType call(_ArgType arg) override {
			return (obj->*method)(arg);
		}
	private:
		_ObjType*	obj;
		_RetType(_ObjType::*method)(_ArgType);
	};

	template<typename _ObjType, typename _ArgType>
	class ObjCallback<_ObjType, _ArgType, void> : public ICallback<_ArgType, void> {
	public:
		ObjCallback(_ObjType* _obj = nullptr, void(_ObjType::*_method)(_ArgType) = nullptr) :
			ICallback<_ArgType, void>(), obj(nullptr), method(nullptr) {
			this->set(_obj, _method);
		}
		virtual ~ObjCallback() {}

		virtual bool isValid() const override {
			return ((this->method != nullptr) && (this->obj != nullptr));
		}

		void set(_ObjType* _obj, void(_ObjType::*_method)(_ArgType)) {
			this->obj = _obj;
			this->method = _method;
		}

		virtual void call(_ArgType arg) override {
			(obj->*method)(arg);
		}
	private:
		_ObjType*	obj;
		void(_ObjType::*method)(_ArgType);
	};

	template<typename _ObjType>
	class ObjCallback<_ObjType, void, void> : public ICallback<void, void> {
	public:
		ObjCallback(_ObjType* _obj = nullptr, void(_ObjType::*_method)() = nullptr) :
			ICallback<void, void>(), obj(nullptr), method(nullptr) {
			this->set(_obj, _method);
		}
		virtual ~ObjCallback() {}

		virtual bool isValid() const override {
			return ((this->method != nullptr) && (this->obj != nullptr));
		}

		void set(_ObjType* _obj, void(_ObjType::*_method)()) {
			this->obj = _obj;
			this->method = _method;
		}

		virtual void call() override {
			(obj->*method)();
		}
	private:
		_ObjType*	obj;
		void(_ObjType::*method)();
	};
}