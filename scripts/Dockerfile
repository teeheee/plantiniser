FROM python:3-alpine
WORKDIR /usr/src/app
EXPOSE 80
COPY . .
RUN pip install -r requirements.txt
CMD python ota_server.py
