from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy import text
from sqlalchemy.orm import Session
from api.app.database import get_db

router = APIRouter(
    prefix="/heroes"
)

@router.get("/")
def get_all_heroes(db: Session = Depends(get_db)):
    result = db.execute(
        text("SELECT * FROM heroes;")
    ).mappings().all()

    return {
        "heroes": [dict(row) for row in result]
    }

@router.get("/{id}")
def get_one_hero(id: int, db: Session = Depends(get_db)):
    result = db.execute(
        text("SELECT * FROM heroes WHERE id = :id;"),
        {"id": id}
    ).mappings().first()

    if not result:
        raise HTTPException(status_code=404, detail="Hero not found")

    return {
        "hero": dict(result)
    }


