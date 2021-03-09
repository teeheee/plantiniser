pipeline {
    agent none
    stages {
        stage('Test firmware') {
            agent {
                docker { 
                   image 'infinitecoding/platformio-for-ci' 
                   args '-u root:root'
                }
            }
            steps {
                sh 'pio test -e native'
            }
        }
        stage('Building firmware') {
            agent {
                docker { 
                   image 'infinitecoding/platformio-for-ci' 
                   args '-u root:root'
                }
            }
            steps {
                sh 'pio run -e main'
            }
        }
        stage ('Deploy firmware') {
            environment {
                VERSION = """${sh (
                    script: 'git rev-list --count HEAD',
                    returnStdout: true
                ).trim()}"""
            }
            agent any
            steps{
                sshagent(credentials : ['alex_sshkey'])
                {
                    sh "scp -o StrictHostKeyChecking=no ./.pio/build/main/firmware.bin alex@192.168.178.2:~/plantiniser_firmware_provider/opt/${env.VERSION}.bin"
                }
            }
        }
        stage('Building image') {
            agent any
            steps{
                script {
                    dockerImage = docker.build("local/plantiniser_firmware_provider","scripts")
                }
            }
        }
    }
}
