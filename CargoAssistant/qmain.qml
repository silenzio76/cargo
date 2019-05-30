
import Qt3D.Core 2.9
import Qt3D.Render 2.9
import Qt3D.Extras 2.9
import Qt3D.Input 2.0

import QtQuick 2.0
import QtQuick.Scene2D 2.9
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Entity {
    id: sceneRoot

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        position: Qt.vector3d( 0.0, 0.0, 20 )
    }

    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                camera: camera
                clearColor: "white"
            }
            pickingSettings.pickMethod: PickingSettings.TrianglePicking
        },
        InputSettings {}
    ]

    Entity {
        id: bedEntity

        Transform {
            id: bedTransform
            scale: 1
            translation: Qt.vector3d( 0, 0, bedCtrls.bedCentreZ )
            rotation: fromEulerAngles( bedCtrls.rotationX,
                                       bedCtrls.rotationY,
                                       bedCtrls.rotationZ )
        }

        Mesh {
            id: bedMesh
            source: "qrc:/obj/plan"
        }

        PhongMaterial {
            id: bedMaterial
            diffuse: Qt.rgba( bedCtrls.colorR/255,
                              bedCtrls.colorG/255,
                              bedCtrls.colorB/255, 1.0 )
            ambient: Qt.rgba( 0.1, 0.1, 0.1, 1.0 )
            shininess: bedCtrls.shininess
        }

        components: [ bedTransform, bedMesh, bedMaterial ]
    }

    Entity {
        id: cube

        components: [cubeTransform, cubeMaterial, cubeMesh, cubePicker]

        property real rotationAngle: 0

        Behavior on rotationAngle {
            enabled: bedCtrls.enabled
            RotationAnimation {
                direction: RotationAnimation.Shortest
                duration: 450
            }
        }

        RotationAnimation on rotationAngle {
            running: !bedCtrls.enabled
            loops: Animation.Infinite
            from: 0; to: 360
            duration: 4000
            onStopped: cube.rotationAngle = 0
        }

        Transform {
            id: cubeTransform
            translation: Qt.vector3d(2, 0, 10)
            scale3D: Qt.vector3d(1, 4, 1)
            rotation: fromAxisAndAngle(Qt.vector3d(0,1,0), cube.rotationAngle)
        }

        CuboidMesh {
            id: cubeMesh
        }

        ObjectPicker {
            id: cubePicker
            hoverEnabled: true
            dragEnabled: true

            // Explicitly require a middle click to have the Scene2D grab the mouse
            // events from the picker
            onPressed: {
                if (pick.button === PickEvent.MiddleButton) {
                    qmlTexture.mouseEnabled = !qmlTexture.mouseEnabled
                    bedCtrls.enabled = !bedCtrls.enabled
                }
            }
        }

        TextureMaterial {
            id: cubeMaterial
            texture: offscreenTexture
        }

        Scene2D {
            id: qmlTexture
            output: RenderTargetOutput {
                attachmentPoint: RenderTargetOutput.Color0
                texture: Texture2D {
                    id: offscreenTexture
                    width: 256
                    height: 1024
                    format: Texture.RGBA8_UNorm
                    generateMipMaps: true
                    magnificationFilter: Texture.Linear
                    minificationFilter: Texture.LinearMipMapLinear
                    wrapMode {
                        x: WrapMode.ClampToEdge
                        y: WrapMode.ClampToEdge
                    }
                }
            }

            entities: [ cube ]
            mouseEnabled: false

            bedCtrls {
                id: bedCtrls
                width: offscreenTexture.width
                height: offscreenTexture.height
            }
        }
    }
}
