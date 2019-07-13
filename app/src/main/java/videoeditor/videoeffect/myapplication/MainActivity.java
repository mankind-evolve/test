package videoeditor.videoeffect.myapplication;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.SurfaceView;
import android.widget.TextView;

import java.nio.ByteBuffer;

import videoeditor.videoeffect.opengl.NativeOpengl;
import videoeditor.videoeffect.opengl.WLSurfaceView;

public class MainActivity extends AppCompatActivity {

    private WLSurfaceView surfaceview;
    private NativeOpengl nativeOpengl;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        surfaceview = findViewById(R.id.surfaceview);
        nativeOpengl = new NativeOpengl();
        surfaceview.setNativeOpengl(nativeOpengl);

        final Bitmap bitmap = BitmapFactory.decodeResource(getResources(),R.drawable.q3);
        ByteBuffer byteBuffer = ByteBuffer.allocate(bitmap.getHeight() * bitmap.getWidth() * 4);
        bitmap.copyPixelsToBuffer(byteBuffer);
        byteBuffer.flip();
        byte[] pixels = byteBuffer.array();
        nativeOpengl.imgData(bitmap.getWidth(),bitmap.getHeight(),pixels.length,pixels);


    }


}
