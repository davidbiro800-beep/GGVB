package com.flguard.game;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainActivity extends Activity {

    private GLSurfaceView glView;
    private boolean cheatDialogShown = false;

    static {
        System.loadLibrary("flgame");
    }

    public native void nativeInit(int width, int height);
    public native void nativeSurfaceChanged(int width, int height);
    public native void nativeRender();
    public native void nativeTouchEvent(int action, int pointerId, float x, float y);
    public native void nativeRestart();
    public native void nativeCleanup();
    public native boolean nativeIsCheatDetected();
    public native boolean nativeIsGameOver();
    public native int nativeGetScore();
    public native int nativeGetHealth();
    public native int nativeGetWave();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        glView = new GLSurfaceView(this);
        glView.setEGLContextClientVersion(3);
        glView.setPreserveEGLContextOnPause(true);

        glView.setRenderer(new GLSurfaceView.Renderer() {
            @Override
            public void onSurfaceCreated(GL10 gl, EGLConfig config) {
                int w = glView.getWidth();
                int h = glView.getHeight();
                if (w <= 0) w = 1080;
                if (h <= 0) h = 1920;
                nativeInit(w, h);
            }

            @Override
            public void onSurfaceChanged(GL10 gl, int width, int height) {
                nativeSurfaceChanged(width, height);
            }

            @Override
            public void onDrawFrame(GL10 gl) {
                nativeRender();
            }
        });

        glView.setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);

        glView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                int action = event.getActionMasked();
                int pointerIndex = event.getActionIndex();
                int pointerId = event.getPointerId(pointerIndex);
                float x = event.getX(pointerIndex);
                float y = event.getY(pointerIndex);

                int nativeAction;
                switch (action) {
                    case MotionEvent.ACTION_DOWN:
                    case MotionEvent.ACTION_POINTER_DOWN:
                        nativeAction = 0;
                        break;
                    case MotionEvent.ACTION_UP:
                    case MotionEvent.ACTION_POINTER_UP:
                        nativeAction = 1;
                        break;
                    case MotionEvent.ACTION_MOVE:
                        nativeAction = 2;
                        for (int i = 0; i < event.getPointerCount(); i++) {
                            nativeTouchEvent(2, event.getPointerId(i),
                                    event.getX(i), event.getY(i));
                        }
                        return true;
                    default:
                        return true;
                }

                nativeTouchEvent(nativeAction, pointerId, x, y);
                return true;
            }
        });

        setContentView(glView);
    }

    public void onCheatDetected() {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (cheatDialogShown) return;
                cheatDialogShown = true;
                AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
                builder.setTitle("CHEAT DETECTED");
                builder.setMessage("Memory tampering detected. The game will be closed.");
                builder.setCancelable(false);
                builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        nativeCleanup();
                        finish();
                        System.exit(0);
                    }
                });
                builder.show();
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (glView != null) {
            glView.onResume();
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (glView != null) {
            glView.onPause();
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        nativeCleanup();
    }
}
