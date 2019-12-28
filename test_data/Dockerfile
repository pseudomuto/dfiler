FROM conanio/gcc9
RUN pip install gcovr
WORKDIR /app
COPY . .
RUN sudo chown -R conan ./
