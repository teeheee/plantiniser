pipeline {
    agent {
        docker { 
           image 'infinitecoding/platformio-for-ci' 
           args '-u root:root'
        }
    }
    stages {
        stage('Build') {
            steps {
                sh 'pio run -e main'
            }
        }
    }
}
