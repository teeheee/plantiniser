pipeline {
    agent {
        docker { image 'eclipse/platformio' }
    }
    stages {
        stage('Build') {
            steps {
                sh 'pio run -e main'
            }
        }
    }
}
