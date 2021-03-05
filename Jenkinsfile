pipeline {
    agent {
        docker { image 'infinitecoding/platformio-for-ci' }
    }
    stages {
        stage('Build') {
            steps {
                sh 'pio run -e main'
            }
        }
    }
}
