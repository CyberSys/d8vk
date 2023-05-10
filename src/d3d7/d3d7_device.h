#pragma once
#include "../ddraw/d3d_include.h"
#include "../ddraw/d3d_wrapped_object.h"
#include "../ddraw/dd7_surface.h"

namespace dxvk {

  class D3D7Device : public WrappedObject<d3d9::IDirect3DDevice9, IDirect3DDevice7>, public AddressLookupTableObject {

  private:
    std::unique_ptr<m_IDirect3DDeviceX> ProxyInterface;
    IDirect3DDevice7 *RealInterface;
    REFIID WrapperID = IID_IDirect3DDevice7;

  public:
    D3D7Device(
        IDirect3DDevice7 *aOriginal,
        d3d9::IDirect3DDevice9* aDevice9 = nullptr,
        IDirectDrawSurface7* pRT = nullptr)
    : Base(aDevice9)
    , RealInterface(aOriginal)
    , m_rt((DD7Surface*)pRT) {
      ProxyInterface = std::make_unique<m_IDirect3DDeviceX>(RealInterface, 7, this);
      ProxyAddressLookupTable.SaveAddress(this, RealInterface);
      if (aDevice9)
        Setup();
    }
    ~D3D7Device() {
      ProxyAddressLookupTable.DeleteAddress(this);
    }

    // FIXME: Remove this.
    IDirect3DDevice7 *GetProxyInterface() {
      return RealInterface;
    }

    /*** IDirect3DDevice7 methods ***/
    STDMETHOD(GetCaps)(THIS_ LPD3DDEVICEDESC7);
    STDMETHOD(EnumTextureFormats)(THIS_ LPD3DENUMPIXELFORMATSCALLBACK, LPVOID);
    STDMETHOD(BeginScene)(THIS);
    STDMETHOD(EndScene)(THIS);
    STDMETHOD(GetDirect3D)(THIS_ LPDIRECT3D7 *);
    STDMETHOD(SetRenderTarget)(THIS_ LPDIRECTDRAWSURFACE7, DWORD);
    STDMETHOD(GetRenderTarget)(THIS_ LPDIRECTDRAWSURFACE7 *);
    STDMETHOD(Clear)(THIS_ DWORD, LPD3DRECT, DWORD, D3DCOLOR, D3DVALUE, DWORD);
    STDMETHOD(SetTransform)(THIS_ D3DTRANSFORMSTATETYPE, LPD3DMATRIX);
    STDMETHOD(GetTransform)(THIS_ D3DTRANSFORMSTATETYPE, LPD3DMATRIX);
    STDMETHOD(SetViewport)(THIS_ LPD3DVIEWPORT7);
    STDMETHOD(MultiplyTransform)(THIS_ D3DTRANSFORMSTATETYPE, LPD3DMATRIX);
    STDMETHOD(GetViewport)(THIS_ LPD3DVIEWPORT7);
    STDMETHOD(SetMaterial)(THIS_ LPD3DMATERIAL7);
    STDMETHOD(GetMaterial)(THIS_ LPD3DMATERIAL7);
    STDMETHOD(SetLight)(THIS_ DWORD, LPD3DLIGHT7);
    STDMETHOD(GetLight)(THIS_ DWORD, LPD3DLIGHT7);
    STDMETHOD(SetRenderState)(THIS_ D3DRENDERSTATETYPE, DWORD);
    STDMETHOD(GetRenderState)(THIS_ D3DRENDERSTATETYPE, LPDWORD);
    STDMETHOD(BeginStateBlock)(THIS);
    STDMETHOD(EndStateBlock)(THIS_ LPDWORD);
    STDMETHOD(PreLoad)(THIS_ LPDIRECTDRAWSURFACE7);
    STDMETHOD(DrawPrimitive)(THIS_ D3DPRIMITIVETYPE, DWORD, LPVOID, DWORD, DWORD);
    STDMETHOD(DrawIndexedPrimitive)(THIS_ D3DPRIMITIVETYPE, DWORD, LPVOID, DWORD, LPWORD, DWORD, DWORD);
    STDMETHOD(SetClipStatus)(THIS_ LPD3DCLIPSTATUS);
    STDMETHOD(GetClipStatus)(THIS_ LPD3DCLIPSTATUS);
    STDMETHOD(DrawPrimitiveStrided)(THIS_ D3DPRIMITIVETYPE, DWORD, LPD3DDRAWPRIMITIVESTRIDEDDATA, DWORD, DWORD);
    STDMETHOD(DrawIndexedPrimitiveStrided)(THIS_ D3DPRIMITIVETYPE, DWORD, LPD3DDRAWPRIMITIVESTRIDEDDATA, DWORD, LPWORD, DWORD, DWORD);
    STDMETHOD(DrawPrimitiveVB)(THIS_ D3DPRIMITIVETYPE, LPDIRECT3DVERTEXBUFFER7, DWORD, DWORD, DWORD);
    STDMETHOD(DrawIndexedPrimitiveVB)(THIS_ D3DPRIMITIVETYPE, LPDIRECT3DVERTEXBUFFER7, DWORD, DWORD, LPWORD, DWORD, DWORD);
    STDMETHOD(ComputeSphereVisibility)(THIS_ LPD3DVECTOR, LPD3DVALUE, DWORD, DWORD, LPDWORD);
    STDMETHOD(GetTexture)(THIS_ DWORD, LPDIRECTDRAWSURFACE7 *);
    STDMETHOD(SetTexture)(THIS_ DWORD, LPDIRECTDRAWSURFACE7);
    STDMETHOD(GetTextureStageState)(THIS_ DWORD, D3DTEXTURESTAGESTATETYPE, LPDWORD);
    STDMETHOD(SetTextureStageState)(THIS_ DWORD, D3DTEXTURESTAGESTATETYPE, DWORD);
    STDMETHOD(ValidateDevice)(THIS_ LPDWORD);
    STDMETHOD(ApplyStateBlock)(THIS_ DWORD);
    STDMETHOD(CaptureStateBlock)(THIS_ DWORD);
    STDMETHOD(DeleteStateBlock)(THIS_ DWORD);
    STDMETHOD(CreateStateBlock)(THIS_ D3DSTATEBLOCKTYPE, LPDWORD);
    STDMETHOD(Load)(THIS_ LPDIRECTDRAWSURFACE7, LPPOINT, LPDIRECTDRAWSURFACE7, LPRECT, DWORD);
    STDMETHOD(LightEnable)(THIS_ DWORD, BOOL);
    STDMETHOD(GetLightEnable)(THIS_ DWORD, BOOL *);
    STDMETHOD(SetClipPlane)(THIS_ DWORD, D3DVALUE *);
    STDMETHOD(GetClipPlane)(THIS_ DWORD, D3DVALUE *);
    STDMETHOD(GetInfo)(THIS_ DWORD, LPVOID, DWORD);

  private:
    void Setup();
    void UploadVertices(void* vertices, DWORD vertexCount, DWORD vertexSize);
    void UploadIndices(void* indices, DWORD indexCount);
    HRESULT InitTexture(DD7Surface* surf, bool renderTarget = false);

    DD7Surface* m_rt = nullptr;

    Com<d3d9::IDirect3DSurface9> m_initialRT;
    Com<d3d9::IDirect3DSurface9> m_initialDS;

    size_t m_ibSize = 0;
    Com<d3d9::IDirect3DIndexBuffer9>  m_IB;
  };

}
