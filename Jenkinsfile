pipeline {
    agent none
    stages {
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
            agent any
            steps{
                script {
                    commitId = sh(returnStdout: true, script: 'git rev-list --count HEAD') 
                }
                sshagent(credentials : ['alex'])
                {
                    sh 'scp ./.pio/build/main/firmware.bin alex@doerte:~/plantiniser_firmware_provider/opt/'+commitId+'.bin'
                }
            }
        }
        stage('Building image') {
            agent any
            steps{
                script {
                    dockerImage = docker.build("local:plantiniser_firmware_provider","scripts")
                }
            }
        }
    }
}
