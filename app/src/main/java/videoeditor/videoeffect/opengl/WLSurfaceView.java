package videoeditor.videoeffect.opengl;

import android.content.Context;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class WLSurfaceView extends SurfaceView implements SurfaceHolder.Callback {

    private NativeOpengl nativeOpengl;


    public void setNativeOpengl(NativeOpengl nativeOpengl) {
        this.nativeOpengl = nativeOpengl;
    }



    public WLSurfaceView(Context context) {
        this(context,null);
    }

    public WLSurfaceView(Context context, AttributeSet attrs) {
        this(context, attrs,0);
    }

    public WLSurfaceView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        getHolder().addCallback(this);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        if(nativeOpengl != null){
            nativeOpengl.surfaceCreate(holder.getSurface());
        }

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        if(nativeOpengl != null){
            nativeOpengl.surfaceChange(width,height);
        }
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }
}
