pipeline {
    agent {
        docker { image 'sglahn/platformio-core' }
    }
    stages {
        stage('Build') {
            steps {
                sh 'pio run -e main'
            }
        }
    }
}
