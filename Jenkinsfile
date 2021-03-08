pipeline {
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
        stage('Building image') {
            steps{
                script {
                    dockerImage = docker.build("local:plantiniser_firmware_provider","scripts")
                }
            }
        }
    }
}
