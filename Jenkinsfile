pipeline {
    agent {
        docker { image 'shaguarger/platformio' }
    }
    stages {
        stage('Build') {
            steps {
                sh 'pio run -e main'
            }
        }
    }
}
