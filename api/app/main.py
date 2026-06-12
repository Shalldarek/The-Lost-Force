from fastapi import FastAPI
from api.app.routers import heroes

app = FastAPI(
    title="The Lost Force",
    description="Front-end representation of the backend side",
    version="1.0"
)

app.include_router(heroes.router)