pipeline {
    agent {
        docker { image 'eclipse/platformio' }
    }
    stages {
        stage('Test') {
            steps {
                sh 'pio test -e native'
            }
        }
        stage('Build') {
            steps {
                sh 'pio run -e main'
            }
        }
    }
}
