#pragma once

#include <Unsorted.h>
#include <Objbase.h>

class YRComHelpers {
public:
	// releases the object and clears the pointer
	template<typename T>
	static void Release(T* &ptr) {
		if(ptr) {
			ptr->Release();
			ptr = nullptr;
		}
	}

	// copies an object from source to target, maintaining
	// a proper reference count.
	template<typename T>
	static void Copy(T* &target, T* &source) {
		auto old = target;
		if(target != source) {
			target = source;
			if(source) {
				source->AddRef();
			}
			Release(old);
		}
	}

	// moves an object from source to target and clears the source
	template<typename T>
	static void Move(T* &target, T* &source) {
		Copy(target, source);
		Release(source);
	}

	template <typename T>
	static HRESULT CreateInstance(const IID& rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, T* &rpv) {
		static_assert(std::is_base_of<IUnknown, T>::value, "T has to be derived from IUnknown.");

		Release(rpv);
		return CreateInstance(rclsid, pUnkOuter, dwClsContext, __uuidof(T), reinterpret_cast<LPVOID*>(&rpv));
	}

	static HRESULT CreateInstance(const IID& rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, const IID& riid, LPVOID* ppv) {
		if(dwClsContext & (CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER)) {
			IUnknown* pIUnknown = nullptr;
			HRESULT hr = CoCreateInstance(rclsid, pUnkOuter, dwClsContext, __uuidof(IUnknown), reinterpret_cast<LPVOID*>(&pIUnknown));
			if(SUCCEEDED(hr)) {
				hr = OleRun(pIUnknown);
				if(SUCCEEDED(hr)) {
					hr = pIUnknown->QueryInterface(riid, ppv);
				}
				pIUnknown->Release();
			}
			return hr;
		} else {
			return CoCreateInstance(rclsid, pUnkOuter, dwClsContext, riid, ppv);
		}
	}
};

template<typename T>
class TClassFactory : public IClassFactory
{
public:
	TClassFactory()
	{
		this->nRefCount = 0;
	}

	virtual HRESULT __stdcall QueryInterface(const IID& riid, void** ppvObject) override
	{
		if (!ppvObject)
			return E_POINTER;

		*ppvObject = nullptr;

		if (riid == __uuidof(IUnknown) || riid == __uuidof(IClassFactory))
			*ppvObject = this;

		if (!ppvObject)
			return E_NOINTERFACE;

		this->AddRef();

		return S_OK;
	}

	virtual ULONG __stdcall AddRef() override
	{
		return Imports::InterlockedIncrement(&this->nRefCount);
	}

	virtual ULONG __stdcall Release() override
	{
		int nNewRef = Imports::InterlockedIncrement(&this->nRefCount);
		if (!nNewRef)
			GameDelete(this);
		return nNewRef;
	}

	virtual HRESULT __stdcall CreateInstance(IUnknown* pUnkOuter, const IID& riid, void** ppvObject) override
	{
		if (!ppvObject)
			return E_INVALIDARG;

		*ppvObject = nullptr;
		if (pUnkOuter)
			return CLASS_E_NOAGGREGATION;

		T* pThis = GameCreate<T>();
		if (!pThis)
			return E_OUTOFMEMORY;

		HRESULT hr = pThis->QueryInterface(riid, ppvObject);

		if (FAILED(hr))
			GameDelete(pThis);

		return hr;
	}

	virtual HRESULT __stdcall LockServer(BOOL fLock) override
	{
		this->nRefCount += fLock ? 1 : -1;

		return S_OK;
	}

private:
	int nRefCount {0};
};